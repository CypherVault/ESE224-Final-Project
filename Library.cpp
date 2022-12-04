#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cctype>
#include "Library.h"
#include <cstring>
#include <fstream>
#include <list>
#define debugout std::cerr


Library::Library() {
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
    consec_id = 0;

    books.open("book.txt");
    if (books.fail()) {
        std::cerr << "Could not open books file!" << std::endl;
        exit(1);
    }

    users.open("student.txt");
    if (users.fail()) {
        std::cerr << "Could not open credentials file!";
        exit(1);
    }

    catalog.push_back({ -1, "", "", "", -1, -1 });  // Invalid book in catalog to return pointers as


    fill_creds();


    std::ofstream credsout("json/credentials.json");
    credsout << std::setw(4) << credentials << std::endl;

    while (!books.eof()) {
        books >> isbn >> title >> author >> category >> copies;
        resandlikes[std::to_string(isbn)] = {
            {"reservers", {}},
            {"likes", 0},
            {"title", title},
            {"reserver_days_passed", 0}
        };
        for (int i = 0; i < copies; ++i) {
            book = { isbn, title, author, category, consec_id, -1 };
            this->catalog.push_back(book);
            json to_add = {
                {"isbn", isbn},
                {"title", title},
                {"author", author},
                {"category", category},
                {"id", consec_id},
                {"due_in", -1}
            };
            catjson[std::to_string(consec_id)] = to_add;
            consec_id++;
        }
    }
    number_of_books = catalog.size();
    /*
    for (auto it : catjson) {
        std::cout << it << std::endl;
    }
     */
    /*
    std::ofstream catout("json/catout.json");
    std::ofstream lnrout("json/resandlikes.json");
    catout << std::setw(4) << catjson << std::endl;
    lnrout << std::setw(4) << resandlikes << std::endl;
     */
    // update_catjson_with_catalog();
    update_catalog_with_catjson();
    // update_resandlikes_with_internal_lnr();
    update_internal_lnr_with_resandlikes();
}

bool Library::borrower_is_first_in_line(long long int isbn, std::string username) {
    for (LikesAndReservers lnr : internal_lnr) {
        if (lnr.isbn == isbn && \
            (lnr.reservers.empty() || lnr.reservers.front() == username)) {
            return 1;
        }
    }
    return 0;
}

int Library::remaining_copies_of_title(std::string title) {
    int rem_copies = 0;
    for (Book book : catalog) {
        if (book.title == title && book.due_in == -1) {
            rem_copies++;
        }
    }
    return rem_copies;
}

void Library::save_all_jsons_to_file() {
    std::ofstream catout("json/catout.json");
    std::ofstream resandlikes_json("json/resandlikes.json");
    catout << std::setw(4) << catjson << std::endl;
    resandlikes_json << std::setw(4) << resandlikes << std::endl;
}

void Library::update_catalog_with_catjson() {
    catalog.clear();
    for (auto it = catjson.begin(); it != catjson.end(); ++it) {
        Book to_add = {
            it.value()["isbn"],
            it.value()["title"],
            it.value()["author"],
            it.value()["category"],
            it.value()["id"],
            it.value()["due_in"]
        };
        catalog.push_back(to_add);
    }
    std::sort(catalog.begin(), catalog.end(),
              [](Book a, Book b) {
                  return a.id < b.id;
              });
}

void Library::update_catjson_with_catalog() {
    for (Book book : catalog) {
        catjson[std::to_string(book.id)] = {
            {"author", book.author},
            {"category", book.category},
            {"due_in", book.due_in},
            {"id", book.id},
            {"isbn", book.isbn},
            {"title", book.title}
        };
    }
}

void Library::update_resandlikes_with_internal_lnr() {
    for (LikesAndReservers lnr : internal_lnr) {
        resandlikes[std::to_string(lnr.isbn)] = {
            {"likes", lnr.likes},
            {"reservers", lnr.reservers},
            {"title", lnr.title},
            {"reserver_days_passed", lnr.reserver_days_passed}
        };
    }
}
void Library::JsonParser(){

 for (Book book : catalog) {
        print_book(book);
    };

};



void Library::update_internal_lnr_with_resandlikes() {
    internal_lnr.clear();
    char *end;
    for (auto it = resandlikes.begin(); it != resandlikes.end(); ++it) {
        std::list<std::string> reservers_vector;
        for (auto resit = (*it)["reservers"].begin(); resit != (*it)["reservers"].end(); ++resit) {
            reservers_vector.push_back(*resit);
        }
        internal_lnr.push_back({
            std::strtoll(it.key().c_str(), &end, 10),
            it.value()["title"],
            reservers_vector,
            it.value()["likes"],
            it.value()["reserver_days_passed"]
        });
    }
}

void Library::print_top_books() {
    int rank = 1;
    for (LikesAndReservers data : internal_lnr) {
        if (data.likes) {
            std::cout << "#" << rank++ << ": " << data.title << " (" << data.likes << ")" << std::endl;
        }
    }
}

void Library::sort_vector_lnr() {
    std::sort(internal_lnr.begin(), internal_lnr.end(),
              [](LikesAndReservers a, LikesAndReservers b) {
                  return a.likes > b.likes;
              });
}

void Library::increment_likes(int id) {
    auto strisbn = std::to_string(search_id(id)->isbn);
    int cur_likes = resandlikes[strisbn]["likes"];
    resandlikes[strisbn]["likes"] = cur_likes += 1;
}

void Library::print_book(Book book) {
    std::cout << "ISBN:     " << book.isbn << std::endl;
    std::cout << "Title:    " << book.title << std::endl;
    std::cout << "Author:   " << book.author << std::endl;
    std::cout << "Category: " << book.category << std::endl;
    std::cout << "Intrn ID: " << book.id << std::endl;
    std::cout << "Due in:   " << book.due_in << std::endl << std::endl;
}

Book* Library::binary_search_catalog(int id, int start, int end) {
    if (start <= end) {
        int mid = (start + end) / 2;
        if (catalog[mid].id == id) {
            return &catalog[mid];
        }
        if (catalog[mid].id > id) {
            return binary_search_catalog(id, start, mid - 1);
        }
        if (catalog[mid].id < id) {
            return binary_search_catalog(id, mid + 1, end);
        }
    }
    return &catalog[0];
}

void Library::print_books_vector(std::vector<Book> bookvec) {
    for (Book book : bookvec) {
        print_book(book);
    }
}

void Library::print_all_books() {
    for (Book book : catalog) {
        print_book(book);
    }
};

void Library::print_internal_lnr() {
    for (LikesAndReservers lnr_it : internal_lnr) {
        std::cout << "ISBN:      " << lnr_it.isbn << std::endl;
        std::cout << "Title:     " << lnr_it.title << std::endl;
        std::cout << "Likes:     " << lnr_it.likes << std::endl;
        std::cout << "Reservers: "; print_list(lnr_it.reservers);
        std::cout << std::endl << std::endl;
    }
}

Book Library::borrow_book(int id, int borrow_days) {
    Book* bookptr = search_id(id);
    int index = bookptr - &catalog[0];
    catalog[index].due_in = borrow_days;
    return *(bookptr);
}

Book* Library::search_id(int id) {
    return binary_search_catalog(id, 0, this->number_of_books - 1);
}

void Library::return_book(int id) {
    Book* bookptr = search_id(id);
    bookptr->due_in = -1;
}

bool Library::delete_book(int id) {
    Book to_delete = *search_id(id);
    if (to_delete.isbn != -1) {
        int index = search_id(id) - &catalog[0];
        catalog.erase(catalog.begin() + index);
        catalog.shrink_to_fit();
        return true;
    }
    return false;
}

void Library::add_book(long long int isbn, std::string title, std::string author, std::string category) {
    Book book = { isbn, title, author, category, consec_id++, -1 };
    catalog.push_back(book);
    this->number_of_books = catalog.size();
}

int Library::reserve_book(std::string username, std::string target_title) {
    // debugout << "Enter reserve book func\n";
    // debugout << "internal_lnr size: " << internal_lnr.size() << '\n';
    if (remaining_copies_of_title(target_title) != 0) {
        return -3;
    }
    for (int i = 0; i < internal_lnr.size(); ++i) {
        // debugout << "iterator idx: " << i << '\n';
        auto current_iterating_book = internal_lnr[i];
        if (current_iterating_book.title == target_title) {
            // debugout << "inside first if\n";
            if (stllist_contains(current_iterating_book.reservers, username)) {
                // debugout << "inside second if\n";
                return -2;
            }
            // debugout << "Push back " << username << " to reservers\n";
            internal_lnr[i].reservers.push_back(username);
            // debugout << "Done\n";
            return internal_lnr[i].reservers.size();
        }
    }
    std::cerr << "Book not found\n";
    return -1;
}

void Library::update_day(double days) {
    // debugout << "Update catalog\n";
    for (int book_iter = 0; book_iter < catalog.size(); ++book_iter) {
        if (catalog[book_iter].due_in > 0) {
            catalog[book_iter].due_in -= days;
            if (catalog[book_iter].due_in < 0) {
                catalog[book_iter].due_in = 0;
            }
        }
    }
    // Update reservers list
    // debugout << "Enter internal_lnr iteration loop" << std::endl;
    for (int lnr_iter = 0; lnr_iter < internal_lnr.size(); ++lnr_iter) {
        // debugout << "Set lnrptr of idx " << lnr_iter << std::endl;
        auto lnrptr = &internal_lnr[lnr_iter];
        // debugout << lnrptr->reserver_days_passed << std::endl;
        if (!lnrptr->reservers.empty()) {
            // debugout << "Reservers list is not empty:\nIncrementing days_passed" << std::endl;
            lnrptr->reserver_days_passed += days;
            // debugout << "Enter days_passed decrement loop\n";
            while (lnrptr->reserver_days_passed > 5) {
                lnrptr->reserver_days_passed -= 5;
                // debugout << "After decrement: " << lnrptr->reserver_days_passed << std::endl;
                lnrptr->reservers.pop_front();
                if (lnrptr->reservers.empty()) {
                    lnrptr->reserver_days_passed = 0;
                    break;
                }
            }
        } else {
            // // debugout << "Reservers list is empty\n";
            lnrptr->reserver_days_passed = 0;
        }
    }
}

void Library::operator<<(const Book& book) {
    std::cout << "ISBN:     " << book.isbn << std::endl;
    std::cout << "Title:    " << book.title << std::endl;
    std::cout << "Author:   " << book.author << std::endl;
    std::cout << "Category: " << book.category << std::endl;
    std::cout << "Intrn ID: " << book.id;
    //return out;
}

void Library::sort_alphabetically_title(std::vector<Book>& vec) {  // Pass vector of structs. If you want to modify the original vector, call it by reference.
    int sorted = 0;                                       // If you want to return a new vector without modifying the original vector, you need to
    while (sorted < vec.size() - 1) {                     // declare the function return type as std::vector<BookAndDue> and have a temporary vector
        sorted = 0;                                       // inside this function to hold the vector to be worked on (ex. std::vector<BookAndDue> temp = vec;)
        for (int i = 0; i < vec.size() - 1; ++i) {
            if (strcmp(vec[i].title.c_str(), vec[i + 1].title.c_str()) > 0) {  // Make the comparison between the name strings, c_str() is called because strcmp is a C function and can only take in C style strings
                std::swap(vec[i], vec[i + 1]);                               // Swap the vector indices (which are structs) if the name is not in alphabecial order
            }
            else {
                sorted++;
            }
        }
    }
}

/* Search functions by Liz */
std::vector<Book> Library::search_book_isbn(long long int isbn) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.isbn == isbn) {
            values.push_back(book);
        }
    }
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_title(std::string title) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.title == title) {
            values.push_back(book);
        }
    }
    
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_author(std::string author) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.author == author) {
            values.push_back(book);
        }
    }
    
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_category(std::string category) {
    std::vector<Book> values;
    for (Book book : catalog) {
        std::cout << "Query: " << category << ", Compare against: " << book.category << std::endl;
        if (book.category == category) {
            values.push_back(book);
        }
    }

    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::istream& operator>>(std::istream& in, Book& book) {
    std::cout << "ISBN:     ";
    in >> book.isbn;
    std::cout << "Title:    ";
    in >> book.title;
    std::cout << "Author:   ";
    in >> book.author;
    std::cout << "Category: ";
    in >> book.category;
    std::cout << "Intrn ID: ";
    in >> book.id;
    return in;
}

void Library::set_loan_duration(int id, int borrow_days) {
    int index = search_id(id) - &catalog[0];
    catalog[index].due_in = borrow_days;
}

Book Library::get_last_book() {
    return catalog.back();
}

template<typename T> auto stllist_iterator_of(std::list<T> tlist, T target) {
    auto it = tlist.begin();
    for (it; it != tlist.end() && *it != target; std::advance(it, 1)) { }
    return it;
}

template<typename T> void print_list(std::list<T> tlist) {
    auto it = tlist.begin();
    while (it != tlist.end()) {
        std::cout << *it << ", ";
        std::advance(it, 1);
    }
    std::cout << std::endl;
}

template<typename T> bool stllist_contains(std::list<T> tlist, T t) {
    auto it = tlist.begin();
    while (it != tlist.end()) {
        if (*it++ == t) {
            return 1;
        }
    }
    return 0;
}

void Library::add_users(int role, std::string username, std::string password){
 if (!credentials.contains(username)) {
        credentials[username] = {
            {"password", password},
            {"role", role},
            {"username", username}
        };
    }
    else {
        std::cerr << "User named " << username << " already exists!" << std::endl;
    }
}

void Library::search_users(int role, std::string username, std::string password){
 if (!credentials.contains(username)) {
       std::cerr << "User named " << username << " doesnt exist!" << std::endl;  
    }
    else {
       std::cout << "User named " << username << " does exist!" << std::endl;
    }
}

 void Library::erase_name(std::string username){

credentials.erase(credentials.find(username));

 }


void Library::fill_creds() {
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


bool Library::check_auth(std::string id, std::string pw , int role ){
 for (auto it = credentials.begin(); it != credentials.end(); ++it) {
        if (it.value()["username"] == id && it.value()["password"] == pw && it.value()["role"] == role) {
            return true;
        }
    }
    return false;
}