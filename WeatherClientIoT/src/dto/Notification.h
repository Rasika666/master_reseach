#ifndef Notification_H
#define Notification_H

#include "WeatherResponse.h"
#include <Arduino.h>

class Notification
{
    public:
        std::vector<String> &subscribers;
        WeatherResponse weather;

        Notification(std::vector<String> &subscribers, WeatherResponse weather);
        String toJson();
    private:
        void serializeVector(const std::vector<String>& vec, JsonArray jsonArray);
};

#endif