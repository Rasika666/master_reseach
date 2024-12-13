#ifndef AdminUser_H
#define AdminUser_H

#include <Arduino.h>

class AdminUser
{
public:
    String username;
    String password;

    AdminUser() {};
    AdminUser(String username, String password)
        :username(username), password(password) {}
 
};

#endif