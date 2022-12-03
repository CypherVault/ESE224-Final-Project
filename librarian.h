#pragma once
#include <iostream>
#include "Management.h"
#include "Library.h"
#include "Teacher.h"
#include "Student.h"
#include "user.h"
#include "reader.h"


class Librarian : public User{

private:
std::string object_class_typeLibrarian = "Librarian";

public:
Librarian();
int menu(Library &lib, Student &S, Teacher &T, Management &m);
bool check_auth(std::string id, std::string pw, Library &lib, int role);

};