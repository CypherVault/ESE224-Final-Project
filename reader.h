#pragma once
#include <iostream>
#include <string.h>
#include "user.h"


class Reader : public User{
protected:
std::string username;
std::string password;
std::string object_class_type = "";
int per;
int lim;
public:


virtual void get_copies(){
    ;
}

virtual void get_period(){
    ;
}

};

