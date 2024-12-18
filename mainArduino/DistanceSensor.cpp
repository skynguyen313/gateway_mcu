#include "DistanceSensor.h"

// Hàm khởi tạo
DistanceSensor::DistanceSensor(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

// Hàm khởi tạo cảm biến
void DistanceSensor::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Đo khoảng cách (tính bằng cm)
float DistanceSensor::getDistance() {
    // Phát tín hiệu TRIG
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Đo thời gian tín hiệu ECHO
    long duration = pulseIn(echoPin, HIGH);

    // Tính khoảng cách (cm)
    float distance = duration * 0.0343 / 2;

    return distance;
}

// Kiểm tra nếu khoảng cách nhỏ hơn  cm
bool DistanceSensor::isLessThan(float cm) {
    float distance = getDistance();
    return (distance < cm);
}
