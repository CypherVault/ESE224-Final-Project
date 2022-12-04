#include <iostream>
#include <string>
#include "third_party/json.hpp"
#pragma once

class User{
protected:
std::string username;
std::string password;
std::string object_class_type = "";
public:
void setUsrInfo(std::string usrnme, std::string pswrd);
virtual void printInfo(){
    ;
}



};