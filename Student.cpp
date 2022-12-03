#include "Student.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <chrono>


Student::Student() {
    fill_creds();
    for (std::string username : usernames) {
        
        database.push_back({username, {}});
    }
}

StudentData Student::get_userdata(std::istream& in) {
    std::string username;
    std::cout << "Enter a username: ";
    in >> username;
    StudentData invalid = { "INVALID", {} };
    for (StudentData data : database) {
        if (data.username == username) {
            return data;
        }
    }
    return invalid;
}

void Student::print_userdata(StudentData data) {
    if (data.username == "INVALID") {
        std::cout << "User is not in the database." << std::endl;
        return;
    }
    std::cout << "Username: " << data.username << std::endl;
    if (data.borrowed_books.empty()) {
        std::cout << "You have not borrowed any books!" << std::endl;
        return;
    }
    for (Book book : data.borrowed_books) {
        if (book.due_in == 0) {
            std::cout << book.title << " is overdue! Make sure to return it." << std::endl;
        } else {
            std::cout << book.title << " is due in " << (int) book.due_in << " days." << std::endl;
        }
    }
    std::cout << std::endl;
};

///VIRTUAL////

 void Student::get_period(){

std::cout << "\n Students can reserve for a maximum of:" << per << " days.\n";

 };

 void Student::get_copies(){

std::cout << "\n Students can reserve a maximum of:" << lim << " books.\n";

 };

 void Student::printInfo(){

std::cout << "\n This object is of class:" << object_class_type << "\n";

 };


///////////////////////

int Student::index_of_username(std::string username) {
    int not_found = -1, index = 0;
    for (StudentData data : database) {
        if (data.username == username) {
            return index;
        }
        index++;
    }
    return not_found;
}

Book Student::return_book_student(Library lib, int id) {
    Book to_return = {-1, "", "", "", -1, -1};
    int index = 0;
    bool found = false;
    for (Book book : database[index_in_database].borrowed_books) {
        if (book.id == id) {
            to_return = book;
            found = true;
            break;
        }
        index++;
    }
    if (found) {
        database[index_in_database].borrowed_books.erase(database[index_in_database].borrowed_books.begin() + index);
    }
    return to_return;
}

Book Student::renew_book_student(int id) {
    Book invalid = {-1, "", "", "", -1, -1};
    for (int i = 0; i < database[index_in_database].borrowed_books.size(); ++i) {
        if (database[index_in_database].borrowed_books[i].id == id) {
            database[index_in_database].borrowed_books[i].due_in = STUDENT_BORROW_DURATION;
            return database[index_in_database].borrowed_books[i];
        }
    }
    return invalid;
}

bool Student::borrow_book_student(Library lib, int id) {
    Book book = *(lib.search_id(id));
    if (book.isbn == -1) {
        std::cout << "The book was not found!" << std::endl;
        return false;
    }
    if (book.due_in >= 0) {
        std::cout << "That copy is on loan. Please try another ID." << std::endl;
        return false;
    } else {
        book.due_in = STUDENT_BORROW_DURATION;
        database[index_in_database].borrowed_books.push_back(book);
        return true;
    }
}

void Student::update_day(double day) {
    for (int user_iter = 0; user_iter < database.size(); ++user_iter) {
        for (int book_iter = 0; book_iter < database[user_iter].borrowed_books.size(); ++book_iter) {
            if (database[user_iter].borrowed_books[book_iter].due_in > 0) {
                database[user_iter].borrowed_books[book_iter].due_in -= day;
                if (database[user_iter].borrowed_books[book_iter].due_in < 0) {
                    database[user_iter].borrowed_books[book_iter].due_in = 0;
                }
            }
        }
    }
}

int Student::menu(Library &lib) {
    bool success;
    char expression = 'a';
    int commandchosen;
    int query_id;
    int query_int;
    long long int query_isbn;
    double days_passed;
    std::string query_author_name, query_title, query_category;
    std::vector<Book> search_result;
    std::chrono::steady_clock::time_point end;
    Book renewed, returned;

    auto start = std::chrono::steady_clock::now();
    std::cout << "\n+----------------------------+" << std::endl;
    std::cout << "|      Library Options       |" << std::endl;
    std::cout << "+----------------------------+" << std::endl;
    std::cout << "\nYou are logged in as: " << session_username << " (Student)" << std::endl << std::endl;
    std::cout << "(1) - Search Book by ID" << std::endl;
    std::cout << "(2) - Borrow Book" << std::endl;
    std::cout << "(3) - Return Book" << std::endl;
    std::cout << "(4) - Renew Book" << std::endl;
    std::cout << "(7) - View Borrowed Books" << std::endl;
    std::cout << "(8) - Search Book by Keyword" << std::endl;
    std::cout << "(0) - Log Out " << std::endl;
    std::cout << "\nPlease select an option. ";
    std::cout << std::endl << "Enter a command: ";
    std::cin >> expression;
    switch (expression) {
        case '1': {

            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            std::cout << "Enter the ID of the book youd like to search by: ";
            std::cin >> query_id;
            Book result = *(lib.search_id(query_id));
            if (result.isbn == -1) {
                std::cout << "The book with ID " << query_id << " was not found!" << std::endl << std::endl;
            } else {
                lib.print_book(result);
            }
            commandchosen = 1;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            update_day(days_passed);
            break;
        }
        case '2':
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            if (session_has_overdue_books()) {
                std::cout << "You must return overdue books first!" << std::endl;
                break;
            }
            if (session_exceeded_books_limit()) {
                std::cout << "You are at your borrow limit! Return some books first." << std::endl;
                break;
            }
            std::cout << "Enter the ID of the book you would like to borrow: ";
            std::cin >> query_id;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            update_day(days_passed);
            success = borrow_book_student(lib, query_id);
            if (success) {
                lib.set_loan_duration(query_id, STUDENT_BORROW_DURATION);  // ??
            }
            std::cout << std::endl;
            print_userdata(database[index_in_database]);
            commandchosen = 1;
            break;
        case '3':
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            std::cout << "Enter the ID of the book you would like to return: ";
            std::cin >> query_id;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            update_day(days_passed);
            returned = return_book_student(lib, query_id);
            if (returned.isbn != -1) {
                lib.set_loan_duration(query_id, -1);
                std::cout << "Returned " << returned.title << "! Thank you." << std::endl;
            } else {
                std::cout << "You have not borrowed that book! Try another." << std::endl;
            }
            commandchosen = 1;
            break;
        case '4':
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            std::cout << "Enter the ID of the book you would like to renew: ";
            std::cin >> query_id;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            update_day(days_passed);
            renewed = renew_book_student(query_id);
            if (renewed.isbn != -1) {
                lib.set_loan_duration(query_id, STUDENT_BORROW_DURATION);
                std::cout << "Renewed " << renewed.title <<  "! You have " << STUDENT_BORROW_DURATION << " days to return it." << std::endl;
            } else {
                std::cout << "You have not borrowed that book! Try another." << std::endl;
            }
            commandchosen = 1;
            break;
        case '7':
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            update_day(days_passed);
            print_userdata(database[index_in_database]);
            commandchosen = 1;
            break;
        case '8':
            std::cout << "(1) - Search by Title" << std::endl;
            std::cout << "(2) - Search by Name of Author" << std::endl;
            std::cout << "(3) - Search by Category" << std::endl;
            std::cout << "(4) - Search by ISBN" << std::endl;
            std::cout << "Select one option: ";
            do {
                std::cin >> query_int;
                if (query_int == 1) {
                    std::cout << "Enter a title: ";
                    std::cin >> query_title;
                    end = std::chrono::steady_clock::now();
                    days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
                    lib.update_day(days_passed);
                    update_day(days_passed);
                    search_result = lib.search_book_title(query_title);
                } else if (query_int == 2) {
                    std::cout << "Enter an author's name: ";
                    std::cin >> query_author_name;
                    end = std::chrono::steady_clock::now();
                    days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
                    lib.update_day(days_passed);
                    update_day(days_passed);
                    search_result = lib.search_book_author(query_author_name);
                } else if (query_int == 3) {
                    std::cout << "Enter a category: ";
                    std::cin >> query_category;
                    end = std::chrono::steady_clock::now();
                    days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
                    lib.update_day(days_passed);
                    update_day(days_passed);
                    search_result = lib.search_book_category(query_category);
                } else if (query_int == 4) {
                    std::cout << "Enter the ISBN of the book: ";
                    std::cin >> query_isbn;
                    end = std::chrono::steady_clock::now();
                    days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
                    lib.update_day(days_passed);
                    update_day(days_passed);
                    search_result = lib.search_book_isbn(query_isbn);
                } else {
                    std::cout << "Please enter a valid option: ";
                }
            } while (query_int < 1 || query_int > 4);
            lib.print_books_vector(search_result);
            commandchosen = 1;
            break;
        case '0':
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            update_day(days_passed);
            commandchosen = 0;
            break;
        default:
            std::cout << "Invalid command! Try again." << std::endl << std::endl;
    }
    return commandchosen;
}

void Student::fill_creds() {
    std::ifstream student;
    student.open("student.txt");
    int role;
    std::string id, pw;
    while (!student.eof()) {
        student >> role >> id >> pw;
        if (!role) {
            usernames.push_back(id);
            passwords.push_back(pw);
        }
    }
}

bool Student::check_auth(std::string id, std::string pw, Library &lib, int role) {
 return (lib.check_auth(id, pw, role));
};

void Student::print_all_users_in_db() {
    for (StudentData data : database) {
        std::cout << data.username << " ";
    }
    std::cout << std::endl;
}

bool Student::session_has_overdue_books() {
    for (Book book : database[index_in_database].borrowed_books) {
        if (!book.due_in) {
            return true;
        }
    }
    return false;
}

bool Student::session_exceeded_books_limit() {
    return database[index_in_database].borrowed_books.size() < STUDENT_BORROW_LIMIT ? false : true;
}

bool Student::has_borrowed_books(std::string username)
{
    std::vector<StudentData> values;
    for (StudentData data : database)
    {
        if (data.username == username)
            values.push_back(data);
    }
    int index = values.size();
    for (int i = 0; i < index; i++)
    {
        if (values[i].borrowed_books.size() == 0)
        {
            return true;
        }
    }

    return false;
}