// Standard Libraries
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Additional Libraries
#include <ArduinoJson.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
#include "secrets.h"

// Country code, including this is advisable
#define SPOTIFY_MARKET "US"

WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 60000;             // Time between requests (1 minute)
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
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying) {

    Serial.println("--------- Currently Playing ---------");

    // Print if song is playing
    Serial.print("Is Playing: ");
    if (currentlyPlaying.isPlaying) Serial.println("Yes");
    else Serial.println("No");

    // Print current track
    Serial.print("Track: ");
    Serial.println(currentlyPlaying.trackName);
    Serial.print("Track URI: ");
    Serial.println(currentlyPlaying.trackUri);
    Serial.println();

    // Print artists
    Serial.println("Artists: ");
    for (int i = 0; i < currentlyPlaying.numArtists; i++) {
        Serial.print("Name: ");
        Serial.println(currentlyPlaying.artists[i].artistName);
        Serial.print("Artist URI: ");
        Serial.println(currentlyPlaying.artists[i].artistUri);
        Serial.println();
    }

    // Print album
    Serial.print("Album: ");
    Serial.println(currentlyPlaying.albumName);
    Serial.print("Album URI: ");
    Serial.println(currentlyPlaying.albumUri);
    Serial.println();

    // Print progress into song
    long progress = currentlyPlaying.progressMs;        // Duration passed in the song
    long duration = currentlyPlaying.durationMs;        // Length of Song
    Serial.print("Elapsed time of song (ms): ");
    Serial.print(progress);
    Serial.print(" of ");
    Serial.println(duration);
    Serial.println();

    float percentage = ((float)progress / (float)duration) * 100;
    int clampedPercentage = (int)percentage;
    Serial.print("<");
    for (int j = 0; j < 50; j++) {
        if (clampedPercentage >= (j * 2)) Serial.print("=");
        else Serial.print("-");
    }
    Serial.println(">");
    Serial.println();

    // Get album image
    for (int i = 0; i < currentlyPlaying.numImages; i++) {
        Serial.println("------------------------");
        Serial.print("Album Image: ");
        Serial.println(currentlyPlaying.albumImages[i].url);
        Serial.print("Dimensions: ");
        Serial.print(currentlyPlaying.albumImages[i].width);
        Serial.print(" x ");
        Serial.print(currentlyPlaying.albumImages[i].height);
        Serial.println();
    }
    Serial.println("------------------------");
}

void loop() {

    // We send requests for every delayBetweenRequests milliseconds,
    // otherwise the API might time out our application
    if (millis() > requestDueTime) {

        Serial.println("Getting currently playing song:");

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