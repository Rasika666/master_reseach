#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "InfoRequest.h"


InfoRequest::InfoRequest(String timeStamp, Location location, Device device)
    :timeStamp(timeStamp), location(location), device(device) {};

void InfoRequest::serializeOpenPorts(const std::vector<String>& vec, JsonArray jsonArray) {
    for (const String& item : vec) {
        jsonArray.add(item);
    }
};

void InfoRequest::serializeConnectedDevices(const std::vector<ConnectedDevice>& vec, JsonArray jsonArray) {
    for (const ConnectedDevice& item : vec) {
        JsonDocument doc;
        doc["device_id"] = item.device_id;
        doc["device_name"] = item.device_name;
        doc["device_type"] = item.device_type;
        doc["device_manufacturer"] = item.device_manufacturer;
        doc["ip_address"] = item.ip_address;
        doc["mac_address"] = item.mac_address;
        jsonArray.add(doc);
    }
};

void InfoRequest::serializeActiveCommand(const std::vector<ActiveCommand>& vec, JsonArray jsonArray) {
    for (const ActiveCommand& item : vec) {
        JsonDocument doc;
        doc["command"] = item.command;
        doc["status"] = item.status;
        doc["timestamp"] = item.timestamp;
        jsonArray.add(doc);
    }
};


String InfoRequest::toJson() {
    JsonDocument doc;

    doc["timeStamp"] = timeStamp;

    JsonObject loc = doc["location"].to<JsonObject>();
    loc["address"] = location.address;
    loc["latitude"] = location.latitude;
    loc["longitude"] = location.longitude;

    JsonObject deviceObj = doc["device"].to<JsonObject>();
    deviceObj["device_id"] = device.device_id;
    deviceObj["type"] = device.type;
    deviceObj["manufacturer"] = device.manufacturer;
    deviceObj["firmware_version"] = device.firmware_version;
    deviceObj["model"] = device.model;
    deviceObj["hardware_version"] = device.hardware_version;
    deviceObj["last_reboot"] = device.last_reboot;
    deviceObj["uptime"] = device.uptime;
    JsonObject deviceLoc = deviceObj["location"].to<JsonObject>();
    deviceLoc["address"] = device.location.address;
    deviceLoc["latitude"] = device.location.latitude;
    deviceLoc["longitude"] = device.location.longitude;

    String output;
    serializeJson(doc, output);
    return output;
};