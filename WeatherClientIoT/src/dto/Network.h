#ifndef Network_H
#define Network_H

#include <Arduino.h>
#include "ConnectedDevice.h"

class Network
{
public:
    String ip_address;
    String mac_address;
    String ssid;
    String signal_strength;
    std::vector<ConnectedDevice> connected_devices;

    Network(){};
    Network(String ip_address, String mac_address, String ssid, String signal_strength, std::vector<ConnectedDevice> connected_devices)
        :ip_address(ip_address), mac_address(mac_address), ssid(ssid), signal_strength(signal_strength), connected_devices(connected_devices) {};
 
};

#endif