#include "WebSocketManager.h"
#include <Arduino.h>

// Constructor
WebSocketManager::WebSocketManager(const char* serverAddress)
    : serverAddress(serverAddress) {}

// Khởi tạo WebSocket
void WebSocketManager::begin() {
    String url = String(serverAddress);
    
    int protocolIndex = url.indexOf("://");
    if (protocolIndex == -1) {
        Serial.println("Error: Invalid URL format");
        return;
    }
    
    String protocol = url.substring(0, protocolIndex);
    String restOfUrl = url.substring(protocolIndex + 3);
    
    int portIndex = restOfUrl.indexOf(':');
    
    String host = restOfUrl.substring(0, portIndex);
    int port = (portIndex == -1) ? 80 : restOfUrl.substring(portIndex + 1).toInt();

    Serial.print("Attempting to connect to WebSocket server at ");
    Serial.println(host + ":" + String(port));

    webSocket.begin(host.c_str(), port, "/");
    webSocket.onEvent(webSocketEvent); // Đăng ký callback xử lý sự kiện
    Serial.println("WebSocket Manager initialized.");
}

// Hàm lặp WebSocket (được gọi trong `loop`)
void WebSocketManager::loop() {
    webSocket.loop(); // Duy trì kết nối WebSocket
}

// Gửi UID qua WebSocket
void WebSocketManager::send(String message) {
    if (webSocket.isConnected()) {
        webSocket.sendTXT(message);
        Serial.println("Sent message: " + message);
    } else {
        Serial.println("WebSocket not connected. Unable to send message.");
    }
}

// Callback xử lý sự kiện WebSocket
void WebSocketManager::webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.println("WebSocket Disconnected");
            break;
        case WStype_CONNECTED:
            Serial.println("WebSocket Connected");
            break;
        case WStype_TEXT:
            Serial.printf("Message from server: %s\n", payload);
            break;
        case WStype_ERROR:
            Serial.println("WebSocket Error occurred");
            break;
        default:
            Serial.println("Unknown WebSocket event");
            break;
    }
}
