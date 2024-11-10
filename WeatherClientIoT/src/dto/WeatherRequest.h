#ifndef WeatherRequest_H
#define WeatherRequest_H

#include "Location.h"
#include <Arduino.h>

class WeatherRequest
{
public:
    String timeStamp;
    Location location;

    WeatherRequest(String timeStamp, Location location);
    String toJson();
};

#endif