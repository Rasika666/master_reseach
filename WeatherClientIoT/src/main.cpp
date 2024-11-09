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
const char *serverUrl = "http://yourserver.com/api/weather";

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
}

void loop()
{
  Serial.println("Connected to WiFi!");
  delay(1000);

  Location deviceLocation("123 Main St", "40.712776", "-74.005974");
  WeatherRequest request("2024-11-01T13:45:00", deviceLocation);
  String  jsonPayload = request.toJson();
  Serial.println("JSON Payload:");
  Serial.println(jsonPayload);

  // if (WiFi.status() == WL_CONNECTED)
  // {
  //   HTTPClient http;
  //   http.begin(serverUrl);
  //   http.addHeader("Content-Type", "application/json");

  //   int httpResponseCode = http.POST(jsonPayload);

  //   if (httpResponseCode > 0)
  //   {
  //     String response = http.getString();
  //     Serial.println("Response:");
  //     Serial.println(response);
  //   }
  //   else
  //   {
  //     Serial.print("Error code: ");
  //     Serial.println(httpResponseCode);
  //   }
  //   http.end();
  // }
  // else
  // {
  //   Serial.println("WiFi not connected");
  // }
}
