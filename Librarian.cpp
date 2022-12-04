#include "Librarian.h"

Librarian::Librarian(){
    
};

int Librarian::menu(Library &lib, Student &S, Teacher &T, Management &m){

    int success;
    int id_entered;
    std::string usr_entered, pas_entered;
    char expression = 'a';
    int commandchosen;
    int query_id;
    int query_int;
    long long int new_isbn, query_isbn;
    double days_passed;
    std::string query_author_name, query_title, query_category;
    std::string new_title, new_author, new_category;
    std::vector<Book> search_result;
    std::chrono::steady_clock::time_point end;
    Book renewed, returned, deleted;

    auto start = std::chrono::steady_clock::now();
    std::cout << "\n+----------------------------+" << std::endl;
    std::cout << "|      Admin Terminal        |" << std::endl;
    std::cout << "+----------------------------+" << std::endl;
    std::cout << "\nYou are logged in as: " << " (Librarian)" << std::endl << std::endl;
    std::cout << "(1) - Add Books" << std::endl;
    std::cout << "(2) - Delete Books" << std::endl;
    std::cout << "(3) - Search Users" << std::endl;
    std::cout << "(4) - Add Users" << std::endl;
    std::cout << "(5) - Delete Users" << std::endl; 
    std::cout << "(0) - Log Out " << std::endl;
    std::cout << "\nPlease select an option. ";
    std::cout << std::endl << "Enter a command: ";
    std::cin >> expression;
switch (expression) {
    case '1': 
end = std::chrono::steady_clock::now();
        days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
        lib.update_day(days_passed);
            std::cout << "Enter the ISBN, title, author, and category (Separate values by spaces and use snake_case for strings): ";
            std::cin >> new_isbn >> new_title >> new_author >> new_category;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
             T.update_day(days_passed);
             S.update_day(days_passed);
            lib.add_book(new_isbn, new_title, new_author, new_category);
            std::cout << "Added the book! Its internal ID is " << lib.get_last_book().id << "." << std::endl;
            commandchosen = 1;
     

end = std::chrono::steady_clock::now();
        days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
        lib.update_day(days_passed);
break;
        case '2': 
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
            std::cout << "Enter the ID of the book you want to remove from the catalog: ";
            std::cin >> query_id;
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            T.update_day(days_passed);
            S.update_day(days_passed);
            success = lib.delete_book(query_id);
            if (success) {
                std::cout << "Removed book." << std::endl;
            } else {
                std::cout << "Book with ID " << query_id << " does not exist!" << std::endl;
            }
            commandchosen = 1;
    break;
        case '3': 
  end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
 std::cout << "Enter the Username of the user to search for. (Separate values by spaces and use snake_case for strings): ";
            std::cin >> usr_entered;
            lib.search_users(0, usr_entered, "test");
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            T.update_day(days_passed);
            S.update_day(days_passed);
 commandchosen = 1;
    break;
        case '4': 

            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
 std::cout << "Enter the ID, Username, and Password of the new user. Username value must be Unique. (Separate values by spaces and use snake_case for strings): ";
            std::cin >> id_entered >> usr_entered >> pas_entered;
            lib.add_users(id_entered, usr_entered, pas_entered);


            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            T.update_day(days_passed);
            S.update_day(days_passed);
    break;
        case '5': 
        end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
std::cout << "Enter the Username of the user to be deleted: ";
 std::cin >> usr_entered;
m.delete_user(usr_entered, lib , T , S);

            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            T.update_day(days_passed);
            S.update_day(days_passed);

    break;
        case '0': 
            end = std::chrono::steady_clock::now();
            days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
            lib.update_day(days_passed);
             T.update_day(days_passed);
            S.update_day(days_passed);

      std::cout << "Logout initiated.....\n\n\n";
        commandchosen = 0;
    break;
    default:
std::cout << "Invalid command! Try again." << std::endl << std::endl;


}
return commandchosen;
};



bool Librarian::check_auth(std::string id, std::string pw, Library &lib, int role) {
          
 return ( lib.check_auth(id, pw, role) );
};

