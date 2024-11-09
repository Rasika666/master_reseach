#include <ESP8266WiFi.h>
#include <ArduinoJson.h> 

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Server endpoint
const char* serverUrl = "http://yourserver.com/api/weather";


class Location {
  private:
    String address;
    String latitude;
    String longitude;

  public: 
    Location(String address, String latitude, tring longitude) {
      this->address = address;
      this->latitude = latitude;
      this->longitude = longitude;
    }
};

class Device {
  private:
    String device_id;
    String type;
    String manufacturer;
    String model;
    String firmware_version;
    String hardware_version;
    String last_reboot;
    String uptime;
    Location location;

  public:
    Device(String device_id, String type, String manufacturer, 
    String model, String firmware_version, String hardware_version, 
    String last_reboot, String uptime, Location location) {
      this->device_id = device_id;
      this->type = type;
      this->manufacturer = manufacturer;
      this->model = model;
      this->firmware_version = firmware_version;
      this->hardware_version = hardware_version;
      this->last_reboot = last_reboot;
      this->uptime = uptime;
      this->location = location;
    }
};

class WeatherRequest {
  private:
    String timeStamp;
    Location location;

  public:
    WeatherRequest(String timeStamp, Location location) {
      this->timeStamp = timeStamp;
      this->location = location;
    }

  String toJson() {
    StaticJsonDocument<512> doc;

    doc["timeStamp"] = timeStamp;

    JsonObject loc = doc.createNestedObject("location");
    loc["address"] = location.address;
    loc["latitude"] = location.latitude;
    loc["longitude"] = location.longitude;

    String output;
    serializeJson(doc, output);
    return output;
  }
  
};



void setup() {

  // wifi setting
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password;

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");


}

void loop() {

  Location deviceLocation("123 Main St", "40.712776", "-74.005974");
  WeatherRequest request("2024-11-01T13:45:00", deviceLocation);
  String jsonPayload = request.toJson();
  Serial.println("JSON Payload:");
  Serial.println(jsonPayload);

  if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Response:");
            Serial.println(response);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } else {
        Serial.println("WiFi not connected");
    }
 

}
