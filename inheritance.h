#include <iostream>
#include <string>
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



/* use the below code in order to call the virtual fucntion to access the class type and all user pertinent information */



//in main {
//    User *userbase;
//    Student student;
//    Teacher teacher;
//    Librarian librarian;
//    ^^^ class and their objects initializing
//    userbase = &student;
//    userbase->printInfo();
//    ^^^ make a pointer to the student object EQUAL to the base class pointer. Then use that to call the base function.
//    userbase = &teacher;
//    userbase->printInfo();
//    ^^^ make a pointer to the teacher object EQUAL to the base class pointer. Then use that to call the base function.
//    userbase = &librarian;
//    userbase->printInfo();
//    ^^^ make a pointer to the librarian object EQUAL to the base class pointer. Then use that to call the base function.
//}



