#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "InfoRequest.h"


InfoRequest::InfoRequest(String timeStamp, Location location, SystemSettings systemSettings, Control control)
    :timeStamp(timeStamp), location(location), systemSettings(systemSettings), control(control) {};

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

    JsonObject systemSettingsObj = doc["systemSettings"].to<JsonObject>();
    JsonObject systemSettingsAdminUser = systemSettingsObj["admin_user"].to<JsonObject>();
    systemSettingsAdminUser["username"] = systemSettings.admin_user.username;
    systemSettingsAdminUser["password"] = systemSettings.admin_user.password;

    JsonObject systemSettingsSecurity = systemSettingsObj["security"].to<JsonObject>();
    systemSettingsSecurity["firewall_status"] = systemSettings.security.firewall_status;
    systemSettingsSecurity["encryption"] = systemSettings.security.encryption;
    JsonArray systemSettingsSecurityOpenPort = systemSettingsSecurity["open_ports"].to<JsonArray>();
    serializeOpenPorts(*systemSettings.security.open_ports ,systemSettingsSecurityOpenPort);

    JsonObject systemSettingsPolicy = systemSettingsObj["policy"].to<JsonObject>();
    systemSettingsPolicy["auto_updates"] = systemSettings.policy.auto_updates;
    systemSettingsPolicy["last_update_check"] = systemSettings.policy.last_update_check;
    systemSettingsPolicy["update_channel"] = systemSettings.policy.update_channel;

    JsonObject controlObj = doc["control"].to<JsonObject>();
    JsonArray controlActiveCommand = controlObj["active_commands"].to<JsonArray>();
    serializeActiveCommand(control.active_commands, controlActiveCommand);


    String output;
    serializeJson(doc, output);
    return output;
};