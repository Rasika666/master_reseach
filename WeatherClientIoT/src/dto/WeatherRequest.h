#ifndef WeatherRequest_H
#define WeatherRequest_H

#include <string>
#include "Location.h"
#include <Arduino.h>

class WeatherRequest
{
public:
  std::string timeStamp;
  Location location;

  WeatherRequest(const std::string &timeStamp, Location location);
  String toJson();
};

#endif