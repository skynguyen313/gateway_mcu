#include "Buzzer.h"

// Khởi tạo giá trị tĩnh
int Buzzer::buzzerPin = -1;
unsigned long Buzzer::previousMillis = 0;
unsigned long Buzzer::beepDuration = 0;
bool Buzzer::isBuzzerOn = false;

void Buzzer::begin(int pin) {
    buzzerPin = pin;
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); // Đảm bảo bắt đầu ở trạng thái tắt
}

void Buzzer::beep(unsigned long duration) {
    beepDuration = duration;
    isBuzzerOn = true;
    previousMillis = millis();
    digitalWrite(buzzerPin, HIGH); // Bật buzzer
}

void Buzzer::update() {
    if (isBuzzerOn && (millis() - previousMillis >= beepDuration)) {
        digitalWrite(buzzerPin, LOW); // Tắt buzzer
        isBuzzerOn = false;
    }
}
