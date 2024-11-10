#ifndef Temperature_H
#define Temperature_H

#include <Arduino.h>

class Temperature
{
public:
    double current_value;
    double max_value;
    double min_value;
    String unit;

    Temperature() {};
    Temperature(double current_value, double max_value, double min_value, String unit)
        :current_value(current_value), max_value(max_value), min_value(min_value), unit(unit) {}
};

#endif