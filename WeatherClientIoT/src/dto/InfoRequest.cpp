#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "InfoRequest.h"


InfoRequest::InfoRequest(String timeStamp, Location location, Network network)
    :timeStamp(timeStamp), location(location), network(network) {};

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

    JsonObject networkObj = doc["network"].to<JsonObject>();
    networkObj["ip_address"] = network.ip_address;
    networkObj["mac_address"] = network.mac_address;
    networkObj["ssid"] = network.ssid;
    networkObj["ip_address"] = network.ip_address;
    networkObj["signal_strength"] = network.signal_strength;
    JsonArray networkConnectedDevice = networkObj["connected_devices"].to<JsonArray>();
    serializeConnectedDevices(network.connected_devices, networkConnectedDevice);

    String output;
    serializeJson(doc, output);
    return output;
};