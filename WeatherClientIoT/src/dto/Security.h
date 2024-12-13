#ifndef Security_H
#define Security_H

#include <Arduino.h>

class Security
{
public:
    String firewall_status;
    String encryption;
    std::vector<String>* open_ports;

    Security(): open_ports(nullptr) {};
    Security(String firewall_status, String encryption, std::vector<String> &open_ports)
        :firewall_status(firewall_status), encryption(encryption), open_ports(&open_ports) {};
};

#endif