#include "DHTesp.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

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
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void initWifi() {
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.print(".");
  }
  lcd.setCursor(0, 1);
  lcd.print("WiFi Conectado!");
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    lcd.setCursor(0, 1);
    lcd.print("Conectando MQTT");
    if (MQTT.connect(mqtt_id, mqtt_user, mqtt_password)) {
      lcd.setCursor(0, 2);
      lcd.print("MQTT Conectado!");
    } else {
      lcd.setCursor(0, 2);
      lcd.print("Falha MQTT");
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
  lcd.init();
  lcd.backlight();
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

  int potValue = analogRead(pot_pin);
  float phValue = ((potValue / 4095.0) * (8.4 - 7.8)) + 7.8;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(data.humidity, 1) + "%");
  lcd.setCursor(0, 2);
  lcd.print("pH: " + String(phValue, 2));
  lcd.setCursor(0, 3);
  lcd.print("Lum: " + String(luminity_value) + " lux");

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

  MQTT.publish("tago/data/post", buffer, n);

  delay(2000);
}
