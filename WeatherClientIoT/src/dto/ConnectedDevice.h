#ifndef ConnectedDevice_H
#define ConnectedDevice_H

#include <Arduino.h>

class ConnectedDevice
{
public:
    String device_id;
    String device_name;
    String device_type;
    String device_manufacturer;
    String ip_address;
    String mac_address;

    ConnectedDevice(String device_id, String device_name, String device_type, 
    String device_manufacturer, String ip_address, String mac_address)
        : device_id(device_id), device_name(device_name), device_type(device_type), 
        device_manufacturer(device_manufacturer), ip_address(ip_address), mac_address(mac_address) {};
        
 
};

#endif