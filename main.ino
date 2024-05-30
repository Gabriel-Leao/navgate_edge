#include "DHTesp.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

const int dht_pin = 15;
const int pot_pin = 32;
const int ldr_pin = 34;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "mqtt.tago.io";
const int mqtt_port = 1883;
const char* mqtt_id = "gabe_leao_mqtt";
const char* mqtt_user = "magic_lion";
const char* mqtt_password = "4aa32027-5816-4b91-bed9-5fe3b00b30cf";

WiFiClient espClient;
PubSubClient MQTT(espClient);
DHTesp dht_sensor;

void initWifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (MQTT.connect(mqtt_id, mqtt_user, mqtt_password)) {
      Serial.println("Conectado com sucesso ao broker MQTT");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(MQTT.state());
      Serial.println(" tentando novamente em 3 segundos");
      delay(3000);
    }
  }
}

void initMQTT() {
  MQTT.setServer(mqtt_server, mqtt_port);
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;

  initWifi();
}

void setup() {
  Serial.begin(9600);
  dht_sensor.setup(dht_pin, DHTesp::DHT22);
  initWifi();
  initMQTT();
  reconnectMQTT();
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();

  TempAndHumidity data = dht_sensor.getTempAndHumidity();
  int luminity_value = map(analogRead(ldr_pin), 0, 4023, 100, 0);

  // Leitura do valor do potenciômetro
  int potValue = analogRead(pot_pin);
  // Converte o valor do potenciômetro para um valor de pH
  float phValue = ((potValue / 4095.0) * (8.4 - 7.8)) + 7.8;

  // Exibe as leituras do sensor DHT22
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  // Exibe o valor do pH simulado
  Serial.println("PH: " + String(phValue, 2));
  // Exibe o valor do ldr
  Serial.println("Luminosidade: " + String(luminity_value) + " lux");
  Serial.println("---");

  // Cria um JSON com os dados
  DynamicJsonDocument doc(256);
  JsonArray data_array = doc.to<JsonArray>();

  JsonObject temperature = data_array.createNestedObject();
  temperature["variable"] = "temperature";
  temperature["value"] = data.temperature;
  temperature["unit"] = "C";

  JsonObject humidity = data_array.createNestedObject();
  humidity["variable"] = "humidity";
  humidity["value"] = data.humidity;
  humidity["unit"] = "%";

  JsonObject ph = data_array.createNestedObject();
  ph["variable"] = "ph";
  ph["value"] = phValue;

  JsonObject luminity = data_array.createNestedObject();
  luminity["variable"] = "luminity";
  luminity["value"] = luminity_value;
  luminity["unit"] = "%";

  char buffer[256];
  size_t n = serializeJson(doc, buffer);

  // Publica os dados no tópico
  MQTT.publish("tago/data/post", buffer, n);

  delay(2000);
}
