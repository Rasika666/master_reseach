#ifndef SystemSettings_H
#define SystemSettings_H

#include <Arduino.h>
#include "AdminUser.h"
#include "Security.h"
#include "Policy.h"

class SystemSettings
{
public:
    AdminUser admin_user;
    Security security;
    Policy policy;


    SystemSettings() {};
    SystemSettings(AdminUser admin_user, Security security, Policy policy)  
        :admin_user(admin_user), security(security), policy(policy) {};    
 
};

#endif