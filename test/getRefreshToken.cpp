// Standard Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <WiFiClient.h>
#include <WiFiClientSecure.h>

// Additional Libraries
#include <ArduinoJson.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
#include "secrets.h"

#define USE_IP_ADDRESS 1

char scope[] = "user-read-playback-state%20user-modify-playback-state";
char callbackURItemplate[] = "%s%s%s";
char callbackURIProtocol[] = "http%3A%2F%2F";
char callbackURIAddress[] = "%2Fcallback%2F";
char callbackURI[100];

ESP8266WebServer server(80);
WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET);

const char *webpageTemplate =
    R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
  </head>
  <body>
    <div>
     <a href="https://accounts.spotify.com/authorize?client_id=%s&response_type=code&redirect_uri=%s&scope=%s">spotify Auth</a>
    </div>
  </body>
</html>
)";

void handleRoot() {

  char webpage[800];
  sprintf(webpage, webpageTemplate, SPOTIFY_CLIENT_ID, callbackURI, scope);
  server.send(200, "text/html", webpage);

}

void handleCallback() {

  String code = "";
  const char *refreshToken = NULL;
  for(uint8_t i = 0; i < server.args(); i++) {
    if(server.argName(i) == "code") {
      code = server.arg(i);
      refreshToken = spotify.requestAccessTokens(code.c_str(), callbackURI);
    }
  }

  if(refreshToken != NULL) server.send(200, "text/plain", refreshToken);
  else server.send(404, "text/plain", "Failed to load token, check serial monitor");

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  Serial.print(message);
  server.send(404, "text/plain", message);

}

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
  IPAddress ipAddress = WiFi.localIP();
  Serial.println(ipAddress);

  if(MDNS.begin("arduino")) {
    Serial.println("MDNS responder started");
  }

  // Handle HTTPS Verification
  client.setFingerprint(SPOTIFY_FINGERPRINT); // These expire every few months
  // ... or don't!
  //client.setInsecure();

  sprintf(callbackURI, callbackURItemplate, callbackURIProtocol, ipAddress.toString().c_str(), callbackURIAddress);

  server.on("/", handleRoot);
  server.on("/callback/", handleCallback);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {

  MDNS.update();
  server.handleClient();

}