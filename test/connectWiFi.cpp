#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- Replace the following! ------

char ssid[] = "UCSD-GUEST";         // your network SSID (name)
char password[] = "";               // your network password

//------- ---------------------- ------

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Do nothing
}