#include "Button.h"

// Constructor
Button::Button(uint8_t buttonPin, unsigned long debounce) 
    : pin(buttonPin), debounceDelay(debounce), buttonState(true), lastButtonState(true), lastDebounceTime(0) {}

// Phương thức khởi tạo
void Button::begin() {
    pinMode(pin, INPUT_PULLUP); // Kích hoạt điện trở kéo lên
}

// Phương thức đọc trạng thái nút
bool Button::read() {
    bool currentState = digitalRead(pin); // Đọc trạng thái hiện tại của nút

    // Kiểm tra nếu trạng thái nút thay đổi
    if (currentState != lastButtonState) {
        lastDebounceTime = millis(); // Ghi lại thời gian thay đổi
    }

    // Nếu thay đổi ổn định trong khoảng debounceDelay
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentState != buttonState) {
            buttonState = currentState; // Cập nhật trạng thái nút
        }
    }

    lastButtonState = currentState; // Cập nhật trạng thái trước đó
    return buttonState;
}

// Kiểm tra trạng thái nút (nhấn hay không)
bool Button::isPressed() {
    return (read() == LOW); // Trả về true nếu nút được nhấn
}
