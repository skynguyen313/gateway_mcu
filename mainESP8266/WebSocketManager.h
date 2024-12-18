#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <WebSocketsClient.h>

class WebSocketManager {
public:
    WebSocketManager(const char* serverAddress); // Constructor
    void begin();                                // Bắt đầu kết nối WebSocket
    void loop();                                 // Lắng nghe và xử lý WebSocket
    void send(String message);                    // Gửi mesgae qua WebSocket

private:
    WebSocketsClient webSocket;
    const char* serverAddress;

    // Hàm callback xử lý sự kiện WebSocket
    static void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);
};

#endif
