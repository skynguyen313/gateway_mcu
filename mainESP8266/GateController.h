#ifndef GATE_CONTROLLER_H
#define GATE_CONTROLLER_H

#include <Arduino.h> 

class GateController {
public:
    GateController(const char* serverName);
    bool verifyUID1(const String& uid);           // Kiểm tra UID1
    bool verifyUID2(const String& uid);           // Kiểm tra UID2
    void controlGate1(bool open);
    void controlGate2(bool open);                // Điều khiển cổng
  
private:
    const char* serverName;
};

#endif // GATE_CONTROLLER_H
