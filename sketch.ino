#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>
#include <ESP32Servo.h>

// Definições
#define DHTPIN 15
#define SERVO_PIN 4

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dht;
Servo myServo;

float TEMP_LIMITE = 28.0; // °C

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String message = String((char*)payload);
  if (String(topic) == "ods6_iot/agua/config/limite") {
    TEMP_LIMITE = message.toFloat();
    Serial.print("Novo limite de temperatura definido: ");
    Serial.println(TEMP_LIMITE);
    Serial.println(millis());
  }
}

void setup() {
  Serial.begin(115200);
  dht.setup(DHTPIN, DHTesp::DHT22);
  myServo.attach(SERVO_PIN);
  myServo.write(90);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      client.subscribe("ods6_iot/agua/config/limite");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Serial.print("Início leitura: ");
  Serial.println(millis());
  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature)) {
    Serial.println("Erro ao ler a temperatura do DHT22!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(data.temperature);
    Serial.println(" °C");

    char tempString[8];
    dtostrf(data.temperature, 1, 2, tempString);
    client.publish("ods6_iot/agua/temperatura", tempString);
    Serial.print("Após publicação: ");
    Serial.println(millis());


    if (data.temperature > TEMP_LIMITE) {
      myServo.write(0);
      Serial.println("Temperatura alta! Atuador acionado.");
      Serial.print("Servo acionado em: ");
      Serial.println(millis());

      String mensagem = "Temperatura acima de " + String(TEMP_LIMITE) + " °C, atuador acionado.";
      client.publish("ods6_iot/agua/status", mensagem.c_str());

      client.publish("ods6_iot/agua/alerta", "true");
    } else {
      myServo.write(90);
      Serial.println("Temperatura normal. Atuador em repouso.");

      String mensagem = "Temperatura abaixo de " + String(TEMP_LIMITE) + " °C, atuador em repouso.";
      client.publish("ods6_iot/agua/status", mensagem.c_str());

      client.publish("ods6_iot/agua/alerta", "false");
    }
  }

  delay(3000);
}
