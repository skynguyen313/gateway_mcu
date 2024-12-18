#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    // Hàm khởi tạo với chân của buzzer
    static void begin(int pin);

    // Hàm điều khiển buzzer bật trong thời gian xác định
    static void beep(unsigned long duration);

    // Hàm cập nhật trạng thái buzzer (phải gọi trong loop())
    static void update();

private:
    static int buzzerPin;                  // Chân nối với buzzer
    static unsigned long previousMillis;  // Thời gian trước đó
    static unsigned long beepDuration;    // Thời gian "bíp"
    static bool isBuzzerOn;               // Trạng thái bật/tắt của buzzer
};

#endif
