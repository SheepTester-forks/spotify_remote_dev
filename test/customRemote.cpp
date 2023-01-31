// Standard Libraries
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Additional Libraries
#include <ArduinoJson.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
#include "secrets.h"

// Country code, including this is advisable. Button pin
#define SPOTIFY_MARKET "US"
#define BUTTON_PIN D2

WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 30000;             // Time between requests (30-seconds)
unsigned long requestDueTime;                           // Time when request due

void setup() {

    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("");

    // Wait for connection
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Handle HTTPS Verification
    client.setFingerprint(SPOTIFY_FINGERPRINT);

    // Access Spotify API
    Serial.println("Refreshing Access Tokens");
    if(!spotify.refreshAccessToken()) {
        Serial.println("Failed to get access tokens");
    }

    // Configure button as an input
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying) {

    Serial.println("--------- Currently Playing ---------");

    // Print current track
    Serial.print("Track: ");
    Serial.println(currentlyPlaying.trackName);
    Serial.println("");

    // Print artists
    Serial.println("Artists: ");
    for (int i = 0; i < currentlyPlaying.numArtists; i++) {
        Serial.print("Name: ");
        Serial.println(currentlyPlaying.artists[i].artistName);
        Serial.println("");
    }

    Serial.println("------------------------");
}

void loop() {

    // Read button state (pressed or not pressed)
    int buttonState = digitalRead(BUTTON_PIN);

    // We send requests if we hold down the button within the delayBetweenRequests interval
    if (millis() > requestDueTime && buttonState == 0) {

        // Get status code: https://developer.spotify.com/documentation/web-api/
        int status = spotify.getCurrentlyPlaying(printCurrentlyPlayingToSerial, SPOTIFY_MARKET);

        if(status == 200) {
            Serial.println("Successfully got currently playing");
        }
        else if(status == 204) {
            Serial.println("Doesn't seem to be anything playing");
        }
        else {
            Serial.print("Error: ");
            Serial.println(status);
        }

        requestDueTime = millis() + delayBetweenRequests;
    }
}