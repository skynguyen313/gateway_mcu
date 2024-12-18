#include "JSONHelper.h"
#include <ArduinoJson.h>

// Hàm tạo JSON gồm tên thiết bị và giá trị
String JSONHelper::createJSON(String name, String value) {
  return "{\"name\":\"" + name + "\",\"value\":\"" + value + "\"}";
}

// Hàm gửi JSON qua Software Serial
void JSONHelper::sendJSON(String json, SoftwareSerial &serial) {
  serial.println(json);                 // Gửi qua Software Serial
  Serial.println("Sent: " + json);      // Log lại JSON gửi qua Serial Monitor
}

// Hàm nhận JSON từ Software Serial
String JSONHelper::receiveJSON(SoftwareSerial &serial) {
  String receivedJSON = "";

  // Kiểm tra nếu có dữ liệu từ Serial
  if (serial.available()) {
    receivedJSON = serial.readStringUntil('\n'); // Đọc dữ liệu tới khi gặp ký tự xuống dòng
    Serial.println("Received: " + receivedJSON); // Log lại dữ liệu nhận
  }
  return receivedJSON; // Trả về chuỗi JSON đã nhận
}

// Hàm phân tích JSON, nhận giá trị "name" và "value" từ JSON
void JSONHelper::parseJson(String receivedJSON, String &name, String &value) {
  // Tạo một bộ phân tích JSON
  StaticJsonDocument<100> doc;

  // Phân tích chuỗi JSON
  DeserializationError error = deserializeJson(doc, receivedJSON);

  if (error) {
    Serial.println("JSON parsing failed");
    return;
  }

  // Lấy giá trị từ JSON
  name = doc["name"].as<String>();
  value = doc["value"].as<String>();

  // Log các giá trị đã nhận
  Serial.println("Parsed Name: " + name + " - Parsed Value: " + value);
}