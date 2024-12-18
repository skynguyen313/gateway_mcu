
//=====================THƯ VIỆN=================================//
#include <SoftwareSerial.h>
#include "ArduinoJson.h"
#include "JSONHelper.h"
#include "RFIDReader.h"
#include "ServoControl.h"
#include "DistanceSensor.h"
#include "Buzzer.h"
#include "Button.h"
//==============================================================//



//======================KHỞI TẠO ĐỐI TƯỢNG======================//
// Khởi tạo Software Serial (RX = A0, TX = A1)
SoftwareSerial mySerial(A0, A1);
// Khởi tạo đối tượng RFIDReade++r
RFIDReader rfidReader1(10, 8); // SDA trên chân 10, RST trên chân 8 - Cổng vào
RFIDReader rfidReader2(9, 7); // SDA trên chân 9, RST trên chân 7 - Cổng ra
ServoControl servo1(5); // Chân servo cổng vào
ServoControl servo2(6); // Chân servo cổng ra
DistanceSensor distance1(A2, A3); // TRIG chân A2, ECHO chân A3 - Cổng vào
DistanceSensor distance2(A4, A5); // TRIG chân A4, ECHO chân A5 - Cổng ra
Button btn1(3); // Chân button1 - 3
Button btn2(2); // Chân button2 - 2


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

  distance1.begin(); // Khởi tạo DistanceSensor 1
  distance2.begin(); // Khởi tạo DistanceSensor 2

  Buzzer::begin(4); // Khởi tạo buzzer chân số 4
  Buzzer::beep(300); // Bíp trong 300ms

  btn1.begin(); // Khởi tạo nút nhấn
  btn2.begin(); // Khởi tạo nút nhấn
}

void loop() {
  servo1.update();
  servo2.update();
  Buzzer::update(); // Cập nhật trạng thái của buzzer

  String uid1 = rfidReader1.readCard(); // Đọc UID từ thẻ
  delay(50);
  String uid2 = rfidReader2.readCard(); // Đọc UID từ thẻ
  if (uid1 != "") {
    String json = JSONHelper::createJSON("rfid1",uid1); //Tạo JSON từ UID
    JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial
    Buzzer::beep(100);
  }
 
  if (uid2 != "") {
    String json = JSONHelper::createJSON("rfid2",uid2); //Tạo JSON từ UID
    JSONHelper::sendJSON(json, mySerial); // Gửi JSON qua Software Serial
    Buzzer::beep(100);
  }

  String receivedJSON = JSONHelper::receiveJSON(mySerial); // Nhận 1 dòng dữ liệu từ Software Serial
  String name = "";
  String value = "";
  static int angle1 = 0;
  static int angle2 = 0;
  if (receivedJSON != ""){
    JSONHelper::parseJson(receivedJSON, name, value);  // Phân tích JSON nhận được
    if (value != ""){
      if (name == "gate1"){
        angle1 = (value == "true") ? 50 : 0;
        servo1.setTarget(angle1);
      }
      else if (name == "gate2"){
        angle2 = (value == "true") ? 50 : 0;
        servo2.setTarget(angle2);
      }
    }
  }

  if (distance1.isLessThan(3.5)){
    angle1 = 0;
    servo1.setTarget(angle1); // Nếu nhỏ hơn 3.5 cm, servo1 quay 0 độ
  }
  if (distance2.isLessThan(3.5)){
    angle2 = 0;
    servo2.setTarget(angle2); // Nếu nhỏ hơn 3.5 cm, servo2 quay 0 độ
  }

  if (btn1.isPressed()){
    angle1 = (angle1==0) ? 50 : 0;
    servo1.setTarget(angle1);   
  }
  if (btn2.isPressed()){
    angle2 = (angle2==0) ? 50 : 0;
    servo2.setTarget(angle2); 
  }
  

}
