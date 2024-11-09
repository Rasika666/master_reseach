#ifndef Location_H
#define Location_H

#include <string>

class Location
{
public:
  std::string address;
  std::string latitude;
  std::string longitude;

  Location() {}
  Location(const std::string &address, const std::string &latitude, const std::string &longitude)
      : address(address), latitude(latitude), longitude(longitude) {}
};

#endif