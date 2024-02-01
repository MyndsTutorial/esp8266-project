//Bibliotecas que precisamos ter no código
#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
//Variaveis do led

bool stateLedApi;
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 10;

//Sensor ultrassonico
unsigned long lastTimeSensor = 0;
unsigned long timerDelaySensor = 50;

const int trigPin = D6;
const int echoPin = D5;

//velocidade do som e variáveis para cálculos de proporção
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;


void setup() {
  // iniciando a comunicaçãona frequência 155200 que é a capacidade do processador 
  Serial.begin(115200);
  delay(10);

  // Avisando no console que está conectando no wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //Para iniciar o WIFI passamos as variaveis que estão no arquivo config.h
  WiFi.begin(ssid, password);
  // Enquanto o wifi não conectar printar pontinho
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Função get na api para testar se está funcionando ou não a api
  //Iniciando o client 
  WiFiClientSecure client;
  //criando um http client pros metodos(GET,POST,PATCH,PUT,DELETE)
  HTTPClient http;
  //Como a api é https precisamos desativar as verificações
  client.setInsecure(); // Desativando as medidas de segurança do google
  //Iniciando a conexão com a api usando  url
  http.begin(client, "URL do servidor construído na próxima aula");
  //Pegando o códgo http da requisição( 200,404 ETC)
  int httpCode = http.GET();

  if (httpCode > 0) {
    // Se receber um sinal da api positivo 
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }
  //Acendendo o led
  pinMode(D8,OUTPUT);
  http.end();
  // Definindo pinos do arduino
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  // criando o cliente http
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Desativando as medidas de segurança do google
  //fazendo o led piscar assincrono ao sensor
  if ((millis() - lastTimeLed) > timerDelayLed) {
    http.begin(client, "https://teste-iot-professor.onrender.com/led/state-led");
    int httpCode = http.GET();
    String payload = http.getString();
    //Serial.println(payload);
    // Stream& input;
    //iniciando um documento pra armazenar o json
    StaticJsonDocument<54> doc;
    //transformando o json em um arquivo legivel
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    //Após o documento ser um json salvando o state que recebe dentro de uma booleana para acender o led
    bool state = doc["state"]; // true
    //Serial.print(state);
    digitalWrite(D8,state);
    //reiniciando o cronometro
    lastTimeLed = millis();
  }
  // Limpando o sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // dando uma pequena carga no sensor para regular o eletrônico
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lendo a velocidade do som que chega ao leitor echo
  duration = pulseIn(echoPin, HIGH);
  
  // Calculando a distância do som
  distanceCm = duration * SOUND_VELOCITY/2;
  
  if((millis()-lastTimeSensor > timerDelaySensor)){
    // Este código mede se existe algo perto do sensor que capte o sinal
    http.begin(client, "URL da api que criaremos depois");
    http.addHeader("Content-Type", "application/json");
    // Criando um arquivo de json como documento
    StaticJsonDocument<100> SensorDocument;
    SensorDocument["nome"] = "Serializando o json";
    SensorDocument["value"] = distanceCm;

    if(distanceCm < 10 and distanceCm > 5){
      // se a distância do sensor em centimetros for entre 5 e 10 centímetros nós vamos
      // enviar uma mensagem na api dizendo que o carrinho bateu
      char bufferDoJsonEmString[100];
      serializeJson(SensorDocument, bufferDoJsonEmString);
      int httpResponseCode = http.POST(bufferDoJsonEmString);
      String ResponseServer = http.getString();
      //Serial.println(ResponseServer);
    }
    lastTimeSensor = millis();
  }
} 
