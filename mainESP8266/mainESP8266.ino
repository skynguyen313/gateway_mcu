#include <ESP8266WiFi.h>
#include "WifiManager.h"
#include "GateController.h"
#include "WebSocketManager.h"
#include "JSONHelper.h"
#include <SoftwareSerial.h>

// Thông tin kết nối WiFi
const char* ssid = "Shit";
const char* password = "123456789@1235";

// Địa chỉ Django Server server
const char* djServer = "http://192.168.108.85:8000";

// Địa chỉ WebSocket server
const char* wsServer = "ws://192.168.108.85:8080";

WifiManager wifiManager(ssid, password);
GateController gateController(djServer);
WebSocketManager webSocketManager(wsServer);
SoftwareSerial mySerial(D1, D2); // Chân RX, TX của ESP8266

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // Tốc độ baudrate của SoftwareSerial

  wifiManager.connect();  // Kết nối WiFi
  webSocketManager.begin(); // Khởi tạo WebSocket
}

void loop() {
  webSocketManager.loop(); // Duy trì WebSocket

  String receivedJSON = JSONHelper::receiveJSON(mySerial); // Nhận 1 dòng dữ liệu từ Software Serial
  String name = "";
  String value = "";
  if (receivedJSON != ""){
    JSONHelper::parseJson(receivedJSON, name, value);  // Phân tích JSON nhận được
    if (value != ""){
      if (name == "rfid1"){
        bool open = gateController.verifyUID1(value);
        gateController.controlGate1(open); // In ra màn hình Serial
        String json = JSONHelper::createJSON("gate1", open ? "true" : "false"); //Tạo JSON cho cổng
        JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial

        String message = JSONHelper::createJSON("rfid1",value);
        webSocketManager.send(message); // Gửi UID qua WebSocket
      }

      else if (name == "rfid2"){   
        bool open = gateController.verifyUID2(value);
        gateController.controlGate2(open);
        String json = JSONHelper::createJSON("gate2", open ? "true" : "false"); //Tạo JSON cho cổng
        JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial

        String message = JSONHelper::createJSON("rfid2",value);
        webSocketManager.send(message); // Gửi UID qua WebSocket
      }
    }
  }

}