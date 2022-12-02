#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "inheritance.cpp"
#include "Library.h"
#define STUDENT_BORROW_DURATION 30
#define STUDENT_BORROW_LIMIT 5
#define SECONDS_PER_DAY 5

typedef struct StudentData  {
    std::string username;
    std::vector<Book> borrowed_books;
} StudentData;

class Student : public Reader{
    private:
        std::string session_username, session_password;
        std::vector<std::string> usernames;
        std::vector<std::string> passwords;
        std::vector<StudentData> database;
        std::string object_class_type = "Student" ;
        int per = 30;
        int lim = 5;
        int index_in_database;
    public:
        Student();
        StudentData get_userdata(std::istream& in);
        void print_userdata(StudentData data);
        void printInfo();
        void get_copies();
        void get_period();
        int index_of_username(std::string username);
        Book return_book_student(Library lib, int id);
        Book renew_book_student(int id);
        bool borrow_book_student(Library lib, int id);
        void update_day(double day);
        int menu(Library &lib);
        void fill_creds();
        bool check_auth(std::string id, std::string pw);
        void print_all_users_in_db();
        bool session_has_overdue_books();
        bool session_exceeded_books_limit();
};