#ifndef Device_H
#define Device_H

#include <string>
#include "Location.h"

class Device
{
public:
  std::string device_id;
  std::string type;
  std::string manufacturer;
  std::string model;
  std::string firmware_version;
  std::string hardware_version;
  std::string last_reboot;
  std::string uptime;
  Location location;

  Device(const std::string &device_id, const std::string &type, const std::string &manufacturer,
         const std::string &model, const std::string &firmware_version, const std::string &hardware_version,
         const std::string &last_reboot, const std::string &uptime, Location location)
      : device_id(device_id), type(type), manufacturer(manufacturer), model(model), firmware_version(firmware_version), hardware_version(hardware_version), last_reboot(last_reboot), uptime(uptime), location(location) {}
};

#endif