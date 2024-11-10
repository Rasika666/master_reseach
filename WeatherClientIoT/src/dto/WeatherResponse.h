#ifndef WeatherResponse_H
#define WeatherResponse_H

#include <Arduino.h>
#include "Temperature.h"
#include "Humidity.h"
#include "Motion.h"

class WeatherResponse
{
public:
    Temperature temperature;
    Humidity humidity;
    Motion motion;
    String description;

    WeatherResponse() {};
    WeatherResponse(Temperature temperature, Humidity humidity, Motion motion, String description)
        : temperature(temperature), humidity(humidity), motion(motion), description(description) {};
};

#endif