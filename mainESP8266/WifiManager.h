#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>

class WifiManager {
public:
    WifiManager(const char* ssid, const char* password);
    void connect();
    bool isConnected();
  
private:
    const char* ssid;
    const char* password;
};

#endif // WIFI_MANAGER_H
