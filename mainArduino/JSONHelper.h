#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class JSONHelper {
public:
  // Hàm tạo JSON từ UID
  static String createJSON(String name, String value);

  // Hàm gửi JSON qua Software Serial
  static void sendJSON(String json, SoftwareSerial &serial);

  // Hàm nhận JSON từ Software Serial
  static String receiveJSON(SoftwareSerial &serial);

  // Hàm phân tích JSON
  static void parseJson(String receivedJSON, String &name, String &value);
};

#endif
