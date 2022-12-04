#include "Management.h"

Management::Management(){
    std::ifstream users2;
    std::ifstream books, users;
    long long int isbn;
    std::string title;
    std::string author;
    std::string category;
    int copies;
    int role;
    std::string username;
    std::string password;
    Book book;

    users2.open("student.txt");

    if (users2.fail()) {
        std::cerr << "Could not open credentials file for management!";
        exit(1);
    }

    while (!users2.eof()) {
        users2 >> role >> username >> password;
        creds[username] = {
            {"role", role},
            {"username", username},
            {"password", password}
        };
    }
};

bool Management::delete_user(std::string username, Library &lib, Teacher &t , Student &s){
    for (auto it = creds.begin(); it != creds.end(); ++it)
    {
        if (it.value()["role"] == 2)
        {
            lib.erase_name(username); // make this in Library
            std::cout << "User deleted." << std::endl;
            return true;
        }
        else if (it.value()["role"] == 0)
        {
            if (s.has_borrowed_books(username)) {

                lib.erase_name(username); // make this in Library
                lib.remove_user_from_reservers_list(username);
                std::cout << "Student " << username << " has been deleted\n";
                return true;
            }
            else {
                std::cout << "\nUser has books on loan. Cannot be deleted" << std::endl;
                return false;
            }
        }
        else if (it.value()["role"] == 1)
        {
            if (t.has_borrowed_books(username)) {
                lib.erase_name(username); // make this in Library
                lib.remove_user_from_reservers_list(username);
                std::cout << "Teacher " << username << " has been deleted\n";
                return true;
            }
            else {
                std::cout << "\nUser has books on loan. Cannot be deleted" << std::endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}


