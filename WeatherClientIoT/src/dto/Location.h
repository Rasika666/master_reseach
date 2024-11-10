#ifndef Location_H
#define Location_H

#include <Arduino.h>

class Location
{
public:
  String address;
  String latitude;
  String longitude;

  Location() {}
  Location(String address, String latitude, String longitude)
      : address(address), latitude(latitude), longitude(longitude) {}
};

#endif