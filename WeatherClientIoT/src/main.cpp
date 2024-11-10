#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "./dto/Location.h"
#include "./dto/WeatherRequest.h"

// WiFi credentials
// const char *ssid = "SLT-LTE-WiFi";
// const char *password = "2JG78T5HRHQ";
const char *ssid = "rasiphone";
const char *password = "playwithheart";

// Server endpoint
// This will change
const String baseUrl = "http://172.20.10.3:8000/api/v0";
WiFiClient client;

void setup()
{

  // wifi setting
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  randomSeed(analogRead(0));
}

String createFloatRandNumber(int min, int max)
{
  double randomInRange = min + (random(0, 10000) / 10000.0) * (max - min);
  Serial.println("randon number generated [min=" + String(min) + ", max=" + String(max) + " ] => " + String(randomInRange));
  return String(randomInRange);
};

void loop()
{

  Location deviceLocation("123 Main St", createFloatRandNumber(6, 8), createFloatRandNumber(79, 81));
  WeatherRequest request("2024-11-01T13:45:00", deviceLocation);
  String jsonPayload = request.toJson();
  Serial.println("JSON Payload:");
  Serial.println(jsonPayload);

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    // call random number end point
    http.begin(client, baseUrl + "/random-generated-number");
    http.addHeader("Content-Type", "application/json");
    int httpRes_rgn = http.GET();
    if (httpRes_rgn > 0)
    {
      String response = http.getString();
      Serial.println("Response from the /random-generated-number");
      Serial.println(response);
    }
    else if (httpRes_rgn == -1)
    {
      Serial.print("Server not responding");
      return;
    }
    else
    {
      Serial.print("Error code: " + httpRes_rgn);
    }
    http.end();
    delay(500);

    // call Weather end point
    http.begin(client, baseUrl + "/weather-info");
    http.addHeader("Content-Type", "application/json");
    int httpRes_weather = http.POST(jsonPayload);
    if (httpRes_weather > 0)
    {
      String response = http.getString();
      Serial.println("Response from the /weather-info");
      Serial.println(response);
    }
    else if (httpRes_rgn == -1)
    {
      Serial.print("Server not responding");
      return;
    }
    else
    {
      Serial.print("Error code: " + httpRes_weather);
    }
    http.end();
  }
  else
  {
    Serial.println("WiFi not connected");
  }

  delay(2000);
}
