#pragma once
#include <iostream>
#include <string>
#include "Teacher.h"
#include "Student.h"
#include "Library.h"
#include "third_party/json.hpp"



class Management{
protected:
   json creds;


public:
 
Management();

bool delete_user(std::string username, Library lib, Teacher &t , Student &s);

    


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



