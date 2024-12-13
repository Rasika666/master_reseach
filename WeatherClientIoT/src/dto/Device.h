#ifndef Device_H
#define Device_H

#include <Arduino.h>
#include "Location.h"

class Device
{
public:
  String device_id;
  String type;
  String manufacturer;
  String model;
  String firmware_version;
  String hardware_version;
  String last_reboot;
  String uptime;
  Location location;

  
  Device(){};
  Device(String device_id, String type, String manufacturer,
         String model, String firmware_version, String hardware_version,
         String last_reboot, String uptime, Location location)
      : device_id(device_id), type(type), manufacturer(manufacturer),
        model(model), firmware_version(firmware_version), hardware_version(hardware_version), 
        last_reboot(last_reboot), uptime(uptime), location(location) {}
};

#endif