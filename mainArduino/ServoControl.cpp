#include "ServoControl.h"

// Constructor
ServoControl::ServoControl(int pin) {
  servoPin = pin;
  currentAngle = 0;
  targetAngle = 0;
  previousMillis = 0;
}

// Phương thức khởi tạo servo
void ServoControl::begin() {
  servo.attach(servoPin);
  servo.write(currentAngle); // Đặt góc ban đầu là 0 độ
}

// Cập nhật trạng thái servo
void ServoControl::update() {
  unsigned long currentMillis = millis();

  // Kiểm tra nếu đã đủ thời gian giữa các bước
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Điều chỉnh góc servo
    if (currentAngle < targetAngle) {
      currentAngle+=5;
      servo.write(currentAngle);
    } else if (currentAngle > targetAngle) {
      currentAngle-=5;
      servo.write(currentAngle);
    }
  }
}

// Đặt góc mục tiêu
void ServoControl::setTarget(int angle) {
  targetAngle = angle;
}
