#include <iostream>
#include "inheritance.h"
#include "Library.h"
#include "Teacher.h"
#include "Student.h"

class Librarian : public User{

private:
std::string object_class_typeLibrarian = "Librarian";

public:
Librarian();
int menu(Library &lib, Student &S, Teacher &T);
bool check_auth(std::string id, std::string pw);
void add_new_user(int role, std::string username, std::string password);
};