#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <WebSocketsClient.h>

class WebSocketManager {
public:
    WebSocketManager(const char* serverAddress); // Constructor
    void begin();                                // Bắt đầu kết nối WebSocket
    void loop();                                 // Lắng nghe và xử lý WebSocket
    void sendUID(String uid);                    // Gửi UID qua WebSocket

private:
    WebSocketsClient webSocket;
    const char* serverAddress;

    // Hàm callback xử lý sự kiện WebSocket
    static void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);
};

#endif
