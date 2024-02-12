#include ".\config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


bool stateLedApi;
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 10;

unsigned long lastTimeSensor = 0;
unsigned long timerDelaySensor = 50;

const int trigPin = 5;  // D5 on ESP8266 corresponds to GPIO5 on ESP32
const int echoPin = 4;  // D4 on ESP8266 corresponds to GPIO4 on ESP32

#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();
  http.begin(client, "URL do servidor construído na próxima aula");

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }

  pinMode(2, OUTPUT);  // D8 on ESP8266 corresponds to GPIO2 on ESP32
  http.end();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();

  if ((millis() - lastTimeLed) > timerDelayLed) {
    http.begin(client, "https://teste-iot-professor.onrender.com/led/state-led");
    int httpCode = http.GET();
    String payload = http.getString();

    StaticJsonDocument<54> doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    bool state = doc["state"];
    digitalWrite(2, state);  // D8 on ESP8266 corresponds to GPIO2 on ESP32

    lastTimeLed = millis();
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;

  if ((millis() - lastTimeSensor > timerDelaySensor)) {
    http.begin(client, "URL da api que criaremos depois");
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<100> SensorDocument;
    SensorDocument["nome"] = "Serializando o json";
    SensorDocument["value"] = distanceCm;

    if (distanceCm < 10 and distanceCm > 5) {
      char bufferDoJsonEmString[100];
      serializeJson(SensorDocument, bufferDoJsonEmString);
      int httpResponseCode = http.POST(bufferDoJsonEmString);
      String ResponseServer = http.getString();
    }

    lastTimeSensor = millis();
  }
}
