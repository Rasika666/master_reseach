#ifndef Policy_H
#define Policy_H

#include <Arduino.h>

class Policy
{
public:
    boolean auto_updates;
    String last_update_check;
    String update_channel;

    Policy() {};
    Policy(boolean auto_updates, String last_update_check, String update_channel)
        : auto_updates(auto_updates), last_update_check(last_update_check), update_channel(update_channel) {};
};

#endif