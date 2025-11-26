#include "UbidotsEsp32Mqtt.h"
const char *WIFI_SSID = "rede"; 
const char *WIFI_PASS = "senha"; 
const char *UBIDOTS_TOKEN = "seu token"; 
const char *DEVICE_LABEL = "seugrupo"; 
const char *VARIABLE_LABEL = "dbm";
const char *CLIENT_ID = "seu_id"; 
Ubidots ubidots(UBIDOTS_TOKEN, CLIENT_ID); 
const int PUBLISH_FREQUENCY = 3000; 
unsigned long timer;
unsigned long last_publish = 0;
const unsigned long PUBLISH_INTERVAL = PUBLISH_FREQUENCY;


void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
float value1;
void setup(){
  Serial.begin(115200);
  ubidots.setDebug(true); 
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int32_t dBm = WiFi.RSSI();
    if (millis() - last_publish > PUBLISH_INTERVAL) {
      ubidots.add(VARIABLE_LABEL, dBm);
      ubidots.publish(DEVICE_LABEL);
 	Serial.printf("Nível de Sinal Wi-Fi: %d dBm\n", dBm);
      last_publish = millis();
    }
  } else {
    Serial.println("Wi-Fi desconectado! Tentando reconectar...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
  }
}
