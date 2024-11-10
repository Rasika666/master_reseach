#ifndef Motion_H
#define Motion_H

#include <Arduino.h>

class Motion
{
public:
    String last_detected;
    boolean motion_detected;

    Motion() {};
    Motion(String last_detected, boolean motion_detected) 
        :last_detected(last_detected), motion_detected(motion_detected) {};

};

#endif