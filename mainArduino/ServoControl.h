#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h> 
#include <Servo.h>

class ServoControl {
public:
  // Constructor: Khởi tạo với chân servo
  ServoControl(int pin);

  // Phương thức khởi tạo servo
  void begin();

  // Cập nhật trạng thái servo
  void update();

  // Đặt góc mục tiêu
  void setTarget(int angle);

private:
  Servo servo;                  // Đối tượng servo
  int servoPin;                 // Chân servo
  int currentAngle;             // Góc hiện tại
  int targetAngle;              // Góc mục tiêu
  unsigned long previousMillis; // Thời điểm cuối cùng servo thay đổi góc
  const unsigned long interval = 15; // Thời gian giữa các bước (ms)
};

#endif
