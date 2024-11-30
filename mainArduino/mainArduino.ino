
//=====================THƯ VIỆN=================================//
#include <SoftwareSerial.h>
#include "ArduinoJson.h"
#include "JSONHelper.h"
#include "RFIDReader.h"
#include "ServoControl.h"
//==============================================================//



//======================KHỞI TẠO ĐỐI TƯỢNG======================//
// Khởi tạo Software Serial (RX = A0, TX = A1)
SoftwareSerial mySerial(A0, A1);

// Khởi tạo đối tượng RFIDReader
RFIDReader rfidReader1(10, 8); // SDA trên chân 10, RST trên chân 8 - Cổng vào
RFIDReader rfidReader2(9, 7); // SDA trên chân 9, RST trên chân 7 - Cổng ra
ServoControl servo1(5); // Chân servo cổng vào
ServoControl servo2(6); // Chân servo cổng ra
StaticJsonDocument<100> json;
//==============================================================//


//==============================HỆ THỐNG====================//
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  rfidReader1.begin(); // Khởi tạo RFID 1
  rfidReader2.begin();

  servo1.begin(); // Khởi tạo servo1
  servo2.begin(); // Khởi tạo servo2
}

void loop() {
  servo1.update();
  servo2.update();

  digitalWrite(10, LOW); // Kích hoạt Module 1
  digitalWrite(9, HIGH); // Vô hiệu hóa Module 2
  delay(50);
  String uid1 = rfidReader1.readCard(); // Đọc UID từ thẻ
  if (uid1 != "") {
    String json = JSONHelper::createJSON("rfid1",uid1); //Tạo JSON từ UID
    JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial
  }

  digitalWrite(10, HIGH); // Vô hiệu hóa Module 1
  digitalWrite(9, LOW); // Kích hoạt Module 2
  delay(50);
  String uid2 = rfidReader2.readCard(); // Đọc UID từ thẻ
  if (uid2 != "") {
    String json = JSONHelper::createJSON("rfid2",uid2); //Tạo JSON từ UID
    JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial
  }

  String receivedJSON = JSONHelper::receiveJSON(mySerial); // Nhận 1 dòng dữ liệu từ Software Serial
  String name = "";
  String value = "";
  if (receivedJSON != ""){
    JSONHelper::parseJson(receivedJSON, name, value);  // Phân tích JSON nhận được
    if (value != ""){
      if (name == "gate1"){
        int angle = (value == "true") ? 90 : 0;
        servo1.setTarget(angle);
      }
      else if (name == "gate2"){
        int angle = (value == "true") ? 90 : 0;
        servo2.setTarget(angle);
      }
    }
  }

}
