#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "Notification.h"

Notification::Notification(std::vector<String>& subscribers, WeatherResponse weather)
    : subscribers(subscribers), weather(weather) {};

void Notification::serializeVector(const std::vector<String>& vec, JsonArray jsonArray) {
    for (const auto& item : vec) {
        jsonArray.add(item);
    }
}

String Notification::toJson() {

        JsonDocument doc;
        JsonArray array = doc["subscribers"].to<JsonArray>();
        serializeVector(subscribers, array);
        
        JsonObject weatherObj = doc.createNestedObject("weather");

        JsonObject temperatureObj = weatherObj["temperature"].to<JsonObject>();
        temperatureObj["current_value"] = weather.temperature.current_value;
        temperatureObj["max_value"] = weather.temperature.max_value;
        temperatureObj["min_value"] = weather.temperature.min_value;
        temperatureObj["unit"] = weather.temperature.unit;

        JsonObject humidityObj = weatherObj["humidity"].to<JsonObject>();
        humidityObj["current_value"] = weather.humidity.current_value;
        humidityObj["unit"] = weather.humidity.unit;

        JsonObject motionObj = weatherObj["motion"].to<JsonObject>();
        motionObj["last_detected"] = weather.motion.last_detected;
        motionObj["motion_detected"] = weather.motion.motion_detected;

        weatherObj["description"] = weather.description;

        String output;
        serializeJson(doc, output);


        return output;
}

