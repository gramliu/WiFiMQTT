/**
 *  Connects to an MQTT server and publishes analog data
 */

#include <WiFiConfig.h>

WiFiConfig* wifiConfig;

void setup() {
    Serial.begin(115200);
    wifiConfig = new WiFiConfig();
}

void loop() {
    wifiConfig->check_connection();

    int raw = analogRead(A0);
    DynamicJsonDocument doc(1024);
    doc["raw"] = raw;

    String output;
    serializeJson(doc, output);

    wifiConfig->client.publish(wifiConfig->mqtt_config->mqtt_topic,
                               output.c_str());
    wifiConfig->client.loop();
    delay(1000);
}