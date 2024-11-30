#include <Arduino.h>
#include "RFIDReader.h"

// Constructor
RFIDReader::RFIDReader(int sdaPin, int rstPin)
  : rfid(sdaPin, rstPin), sdaPin(sdaPin), rstPin(rstPin) {}

// Khởi tạo RFID
void RFIDReader::begin() {
  SPI.begin();
  rfid.PCD_Init(); // Khởi tạo module RFID
}

// Đọc UID từ thẻ RFID
String RFIDReader::readCard() {
  // Kiểm tra nếu có thẻ trong vùng quét
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return ""; // Không có thẻ
  }

  // Đọc UID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX); // Chuyển từng byte của UID thành chuỗi HEX
    if (i != rfid.uid.size - 1) {
      uid += ":"; // Thêm dấu ':' giữa các byte
    }
  }

  // Ngừng giao tiếp với thẻ
  rfid.PICC_HaltA();
  return uid;
}
