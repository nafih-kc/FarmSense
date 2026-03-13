#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Flask server
const char* serverName = "http://YOUR_SERVER_IP:5000/data";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// Pins
int blue_led = 2;
int green_led = 5;
int ldr = 21;
int moisture = 34;
int pump = 14;

void setup_wifi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("CONNECTING.....");
  }

  Serial.println("CONNECTED");
}

void send_data(String values)
{
  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "data=" + values;

      Serial.println("Sending: " + httpRequestData);

      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response: ");
      Serial.println(httpResponseCode);

      if (httpResponseCode > 0)
      {
        String response = http.getString();
        Serial.println(response);
      }

      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }

    lastTime = millis();
  }
}

void setup()
{
  Serial.begin(9600);

  dht.begin();
  setup_wifi();

  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(moisture, INPUT);
  pinMode(pump, OUTPUT);
}

void loop()
{
  // LDR
  int ldr_val = digitalRead(ldr);
  String light_status;

  Serial.print("LDR value: ");
  Serial.println(ldr_val);

  if (ldr_val == 0)
  {
    digitalWrite(green_led, HIGH);
    light_status = "ON";
  }
  else
  {
    digitalWrite(green_led, LOW);
    light_status = "OFF";
  }

  Serial.print("Light Status: ");
  Serial.println(light_status);

  // Moisture
  int mois_val = analogRead(moisture);

  Serial.print("Moisture value: ");
  Serial.println(mois_val);

  if (mois_val > 3000)
  {
    digitalWrite(pump, HIGH);
  }
  else
  {
    digitalWrite(pump, LOW);
  }

  // DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(h);

  Serial.print("Temperature: ");
  Serial.println(t);

  if (t > 31)
  {
    digitalWrite(blue_led, HIGH);
  }
  else
  {
    digitalWrite(blue_led, LOW);
  }

  // Send data
  String values = String(h) + "," + String(t) + "," + light_status + "," + String(mois_val);

  send_data(values);

  delay(2000);
}

