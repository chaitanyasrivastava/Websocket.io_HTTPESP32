#include <ESP8266WiFi.h>     //
#include <WebSocketsClient.h>

const char* ssid = "Chaitanya";               // Replace with your WiFi SSID
const char* password = "chaitanya";       // Replace with your WiFi Password

const char* host = "192.168.39.133";            // Replace with your PC/server's local IP
const uint16_t port = 3000;                   // WebSocket server port
const char* path = "/";                       // WebSocket endpoint

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED:
      Serial.println("Connected to server");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from server");
      break;
    case WStype_TEXT:
      Serial.printf("Received: %s\n", payload);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected. IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to WebSocket server
  webSocket.begin(host, port, path);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Reconnect every 5 seconds if needed
}

void loop() {
  webSocket.loop();

  // Send alphabetic data every 1 second
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 1000) {
    lastSend = millis();

    // Generate a random uppercase letter from A to Z
    char letter = 'A' + random(0, 26);
    String message = "ESP8266 Data: ";
    message += letter;

    Serial.println("Sending: " + message);
    webSocket.sendTXT(message);
  }
}


