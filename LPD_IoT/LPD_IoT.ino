#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
// #include <WiFiManager.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34 
#define SOIL_TEMP_PIN 25

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(SOIL_TEMP_PIN);
DallasTemperature soilTemperature(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const char* ssid = "realme 12 Pro 5G";
const char* password = "server error";

String serverUrl = "http://Prasanth23.pythonanywhere.com/predict";

String lines[9];
int currentLine = 0;

String extractStringValue(String json, String key) {
  int keyStart = json.indexOf("\"" + key + "\":");
  if (keyStart == -1) return "";

  int valueStart = json.indexOf("\"", keyStart + key.length() + 3); 
  int valueEnd = json.indexOf("\"", valueStart + 1);             

  if (valueStart == -1 || valueEnd == -1) return "";

  return json.substring(valueStart + 1, valueEnd);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  soilTemperature.begin();
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);

}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int soilMoistureRaw = analogRead(SOIL_MOISTURE_PIN);
  float soilMoisture = soilMoistureRaw;
  soilTemperature.requestTemperatures();
  float soilTemp = soilTemperature.getTempCByIndex(0);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Sensor read error!");
    lcd.clear();
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"soil_moisture\":" + String(soilMoisture, 2) +
                  ",\"ambient_temp\":" + String(temperature, 2) +
                  ",\"humidity\":" + String(humidity, 2) +
                  ",\"soil_temp\":" + String(soilTemp, 2) + "}";

    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);

      int pH_idx = response.indexOf("\"pH\":");
      int EC_idx = response.indexOf("\"EC\":");
      int soil_idx = response.indexOf("\"soil_type\":\"");
      int crop_idx = response.indexOf("\"suitable_crop\":\"");

      float pH = response.substring(response.indexOf("\"pH\":") + 5, response.indexOf(",", response.indexOf("\"pH\":"))).toFloat();
      float EC = response.substring(response.indexOf("\"EC\":") + 5, response.indexOf(",", response.indexOf("\"EC\":"))).toFloat();
      String soilType = extractStringValue(response, "soil_type");
      String crop = extractStringValue(response, "suitable_crop");

      lines[0] = "Moisture: " + String(soilMoisture, 1);
      lines[1] = "Amb Temp: " + String(temperature, 1) + " C";
      lines[2] = "Humidity: " + String(humidity, 1) + " %";
      lines[3] = "Soil Temp: " + String(soilTemp, 1) + "C";
      lines[4] = "pH: " + String(pH, 2);
      lines[5] = "EC: " + String(EC, 0);
      lines[6] = "Soil: " + soilType;
      lines[7] = "Crop: " + crop;
      lines[8] = "Reading next...";

    } else {
      Serial.print("HTTP Error: ");
      Serial.println(httpResponseCode);
      lines[0] = "Server Error";
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
    lines[0] = "WiFi Lost!";
  }

  for (int i = 0; i < 9; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(lines[i].substring(0, 16));
    delay(2500);
  }

  delay(1000); 
}