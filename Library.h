#pragma once
#include <vector>
#include <string>
#include <list>
#include "third_party/json.hpp"

using json = nlohmann::json;

typedef struct LikesAndReservers {
    long long int isbn;
    std::string title;
    std::list<std::string> reservers;
    int likes;
} LikesAndReservers;

typedef struct Book {
    long long int isbn;
    std::string title;
    std::string author;
    std::string category;
    int id;
    double due_in;  // -1 if in available, nonnegative (>0) if on loan
} Book;

class Library {
    private:
        std::vector<Book> catalog;
        json catjson;
        json resandlikes;
        json credentials;
        std::vector<LikesAndReservers> internal_rnl;
        int number_of_books;
        int consec_id;
    public:
        Library();
        void print_book(Book book);
        void print_books_vector(std::vector<Book> bookvec);
        void print_all_books();
        Book* binary_search_catalog(int id, int start, int end);
        Book* search_id(int id);
        Book borrow_book(int id, int borrow_days);
        void return_book(int id);
        bool delete_book(int id);
        void add_book(long long int isbn, std::string title, std::string author, std::string category);
        void update_day(double days);
        Book search_catalog_by_id(int id, int start, int end);
        void operator<<(const Book& book);
        void sort_alphabetically_title(std::vector<Book>& vec);
        friend std::istream& operator>>(std::istream& in, const Book& book);
        std::vector<Book> search_book_isbn(long long int isbn);
        std::vector<Book> search_book_title(std::string title);
        std::vector<Book> search_book_category(std::string category);
        std::vector<Book> search_book_author(std::string author);
        void set_loan_duration(int id, int borrow_days);
        Book get_last_book();
        void JsonParser();
        void rnljson_to_vector();
        void sort_vector_lnr();
        void print_top_books();
        void increment_likes(int id);
        int reserve_book(std::string username, std::string target_title);
        void print_internal_rnl();
        void add_users(int role, std::string username, std::string password);
        void search_users(int role, std::string username, std::string password);
};

template<typename T> auto stllist_iterator_of(T t);
template<typename T> void print_list(std::list<T> tlist);
template<typename T> bool stllist_contains(std::list<T> tlist, T t);