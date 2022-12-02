#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "inheritance.cpp"
#include "Library.h"
#define TEACHER_BORROW_DURATION 50
#define TEACHER_BORROW_LIMIT 10
#define SECONDS_PER_DAY 5

typedef struct TeacherData {
    std::string username;
    std::vector<Book> borrowed_books;
} TeacherData;

class Teacher : public Reader{
    private:
        std::string session_username, session_password;
        std::vector<std::string> usernames;
        std::vector<std::string> passwords;
        std::vector<TeacherData> database;
        std::string object_class_type = "Teacher";
        int per = 30;
        int lim = 5;
        int index_in_database;
    public:
        Teacher();
        TeacherData get_userdata(std::istream& in);
        void print_userdata(TeacherData data);
        void printInfo();
        void get_copies();
        void get_period();
        int index_of_username(std::string username);
        Book return_book_teacher(Library lib, int id);
        Book renew_book_teacher(int id);
        bool borrow_book_teacher(Library lib, int id);
        void update_day(double day);
        void request_book(Library lib, long long int isbn, std::string title, std::string author, std::string category);
        int menu(Library &lib);
        void fill_creds();
        bool check_auth(std::string id, std::string pw);
        bool session_has_overdue_books();
        bool session_exceeded_books_limit();
};