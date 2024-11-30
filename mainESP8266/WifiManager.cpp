#include "WifiManager.h"

WifiManager::WifiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WifiManager::connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

bool WifiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
