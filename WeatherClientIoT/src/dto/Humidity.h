#ifndef Humidity_H
#define Humidity_H

#include <Arduino.h>

class Humidity
{
public:
    double current_value;
    String unit;
    
    Humidity() {}
    Humidity(double current_value, String unit)
        : current_value(current_value), unit(unit) {}
};

#endif