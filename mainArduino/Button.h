#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
    uint8_t pin;              // Chân được kết nối với nút
    bool buttonState;         // Trạng thái hiện tại của nút
    bool lastButtonState;     // Trạng thái trước đó của nút
    unsigned long lastDebounceTime; // Thời gian lần cuối nút thay đổi trạng thái
    unsigned long debounceDelay;    // Độ trễ khử nhiễu

public:
    // Constructor
    Button(uint8_t buttonPin, unsigned long debounce = 50);

    // Phương thức khởi tạo
    void begin();

    // Phương thức đọc trạng thái nút
    bool read();

    // Kiểm tra trạng thái nút (nhấn hay không)
    bool isPressed();
};

#endif
