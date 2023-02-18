// Standard Libraries
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Additional Libraries
// #include <ArduinoJson.h>
// #include <SpotifyArduino.h>
// #include <SpotifyArduinoCert.h>
// #include "secrets.h"

// Country code, including this is advisable. Button pin
// #define SPOTIFY_MARKET "US"
// #define BUTTON_PIN D2

// WiFiClientSecure client;
// SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 100;             // Time between requests (10-seconds)
unsigned long requestDueTime;                           // Time when request due

void setup() {

    Serial.begin(115200);

    // WiFi.mode(WIFI_STA);
    // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("");

    // Wait for connection
    // while(WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.print("connecting ");
    // }
    // Serial.println("");
    // Serial.print("Connected to ");
    // Serial.println(WIFI_SSID);
    // Serial.print("IP address: ");
    // Serial.println(WiFi.localIP());

    // // Handle HTTPS Verification
    // client.setFingerprint(SPOTIFY_FINGERPRINT);

    // // Access Spotify API
    // Serial.println("Refreshing Access Tokens");
    // if(!spotify.refreshAccessToken()) {
    //     Serial.println("Failed to get access tokens");
    // }

    // Configure button as an input
    pinMode(D2, INPUT_PULLUP);
    pinMode(D1, INPUT_PULLUP);
}

long count = 0;

void loop() {

auto lmao = digitalRead(D1) == 0;
    // We send requests if we hold down the button within the delayBetweenRequests interval
    if (millis() > requestDueTime ) {
if (digitalRead(D2) == 0) {
  if (lmao) {
    Serial.println("stop pressing both button  .. you fucker");
  } else {

      count ++;
        Serial.print("up...   ");
        Serial.println(count);
  }

        requestDueTime = millis() + delayBetweenRequests;
        } else if (digitalRead(D1) == 0) {
      count --;
        Serial.print("down... ");
        Serial.println(count);

        requestDueTime = millis() + delayBetweenRequests;
        }
    }
}
