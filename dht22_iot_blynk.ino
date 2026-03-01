#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_AUTH_TOKEN "YourAuthToken"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "NamaWiFi";
char pass[] = "PasswordWiFi";
#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendTemperature() {
  float temp = dht.readTemperature();

  if (!isnan(temp)) {
    Blynk.virtualWrite(V0, temp);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendTemperature); // kirim tiap 2 detik
}

void loop() {
  Blynk.run();
  timer.run();
}
