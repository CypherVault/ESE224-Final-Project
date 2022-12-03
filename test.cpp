

#include <iostream>

bool Librarian::check_auth(std::string id, std::string pw) {
    for (auto it = credentials.begin(); it != credentials.end(); ++it) {
        if (it.value()["username"] == id && it.value()["password"] == pw) {
            return true;
        }
    }
    return false;
}

void Managment::fill_creds_from_txt() {
    std::ifstream users("student.txt");
    std::string username, password;
    int role;
    while (!users.eof()) {
        users >> role >> username >> password;
        credentials[username] = {
            {"role", role},
            {"username", username},
            {"password", password}
        };
    }
}


void Library::fill_creds_from_txt() {
    std::ifstream users("student.txt");
    std::string username, password;
    int role;
    while (!users.eof()) {
        users >> role >> username >> password;
        credentials[username] = {
            {"role", role},
            {"username", username},
            {"password", password}
        };
    }
}