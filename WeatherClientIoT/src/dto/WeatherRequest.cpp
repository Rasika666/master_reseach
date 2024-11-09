#include "WeatherRequest.h"
#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include <Arduino.h>

WeatherRequest::WeatherRequest(const std::string &timeStamp, Location location)
    : timeStamp(timeStamp), location(location) {};

String WeatherRequest::toJson()
{
    JsonDocument doc;

    doc["timeStamp"] = timeStamp;

    JsonObject loc = doc["location"].to<JsonObject>();
    loc["address"] = location.address;
    loc["latitude"] = location.latitude;
    loc["longitude"] = location.longitude;

    String output;
    serializeJson(doc, output);
    return output;
};