#ifndef RFID_READER_H
#define RFID_READER_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDReader {
public:
  // Constructor
  RFIDReader(int sdaPin, int rstPin);

  // Khởi tạo RFID
  void begin();

  // Đọc UID từ thẻ RFID, trả về chuỗi UID (rỗng nếu không có thẻ)
  String readCard();

private:
  MFRC522 rfid; // Đối tượng RFID
  int sdaPin;   // Chân SDA
  int rstPin;   // Chân RST
};

#endif
