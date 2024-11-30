#include <ESP8266WiFi.h>
#include "GateController.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Constructor
GateController::GateController(const char* serverName)
    : serverName(serverName) {}

bool GateController::verifyUID1(const String& uid){
  if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        // Thêm UID vào endpoint URL
        String endpoint = String(serverName) + "/api/prove/rfid1/" + uid + "/";
        http.begin(client, endpoint);

        // Gửi GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            if (httpResponseCode == HTTP_CODE_NO_CONTENT) return true; 
        }
        else return false;
        http.end();

    } else {
        Serial.println("Error in WiFi connection");
    }

    return false; // Mặc định là không hợp lệ nếu có lỗi
}

bool GateController::verifyUID2(const String& uid){
  if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        // Thêm UID vào endpoint URL
        String endpoint = String(serverName) + "/api/prove/rfid2/" + uid + "/";
        http.begin(client, endpoint);

        // Gửi GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            if (httpResponseCode == HTTP_CODE_NO_CONTENT) return true; 
        }
        else return false;
        http.end();

    } else {
        Serial.println("Error in WiFi connection");
    }

    return false; // Mặc định là không hợp lệ nếu có lỗi
}


// Điều khiển cổng
void GateController::controlGate1(bool open) {
    if (open) {
        Serial.println("Gate1 is now OPEN");
    } else {
        Serial.println("Gate1 is now CLOSED");
    }
}

void GateController::controlGate2(bool open) {
    if (open) {
        Serial.println("Gate2 is now OPEN");
    } else {
        Serial.println("Gate2 is now CLOSED");
    }
}

