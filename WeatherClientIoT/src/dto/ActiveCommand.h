#ifndef ActiveCommand_H
#define ActiveCommand_H

#include <Arduino.h>

class ActiveCommand
{
public:
    String command;
    String status;
    String timestamp;

    ActiveCommand(String command, String status, String timestamp)
        :command(command), status(status), timestamp(timestamp) {};
};

#endif