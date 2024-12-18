#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>

class DistanceSensor {
private:
    int trigPin; // Chân TRIG của cảm biến
    int echoPin; // Chân ECHO của cảm biến

public:
    // Hàm khởi tạo
    DistanceSensor(int trigPin, int echoPin);

    // Hàm khởi tạo cảm biến (thiết lập chân)
    void begin();

    // Đo khoảng cách (trả về khoảng cách tính bằng cm)
    float getDistance();

    // Kiểm tra nếu khoảng cách nhỏ hơn x cm
    bool isLessThan(float cm);
};

#endif
