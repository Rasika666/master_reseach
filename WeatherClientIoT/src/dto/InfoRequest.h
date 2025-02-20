#ifndef InfoRequest_H
#define InfoRequest_H

#include "Location.h"
#include "Device.h"
#include "Network.h"
#include "SystemSettings.h"
#include "ActiveCommand.h"
#include "Control.h"
#include <Arduino.h>
#include <ArduinoJson.h>

class InfoRequest
{
public:
    String timeStamp;
    Location location;
    SystemSettings systemSettings;

    InfoRequest(String timeStamp, Location location, SystemSettings systemSettings);
    String toJson();

private:
    void serializeOpenPorts(const std::vector<String>& vec, JsonArray jsonArray);
    void serializeConnectedDevices(const std::vector<ConnectedDevice>& vec, JsonArray jsonArray);
    void serializeActiveCommand(const std::vector<ActiveCommand>& vec, JsonArray jsonArray);
};

#endif