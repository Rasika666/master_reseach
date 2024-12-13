#ifndef Control_H
#define Control_H

#include <Arduino.h>
#include "ActiveCommand.h"

class Control
{
public:
   std::vector<ActiveCommand> &active_commands;

   Control(std::vector<ActiveCommand> &active_commands) 
        :active_commands(active_commands) {};
};

#endif