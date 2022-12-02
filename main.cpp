#include "Library.h"
#include "Teacher.h"
#include "Student.h"
#include "librarian.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <chrono>
#define SECONDS_PER_DAY 5

int main() {
	Student student = Student();
	Teacher teacher = Teacher();
	Library library = Library();
	Librarian librarian = Librarian();
	Reader *reader;

	std::string usr;
	std::string pas;
	bool proceed;
	bool valid_student, valid_teacher, valid_librarian;

	while (1) {
		auto start = std::chrono::steady_clock::now();
		std::cout << "Enter username and password, space-separated: ";
		std::cin >> usr;
		std::cin >> pas;

		valid_student = student.check_auth(usr, pas);
		valid_teacher = teacher.check_auth(usr, pas);
		valid_librarian = librarian.check_auth(usr, pas);

		if (!valid_teacher  && !valid_student && !valid_librarian) {
			std::cout << "Invalid login! Please check your username and password" << std::endl;
			continue;
		}
		auto end = std::chrono::steady_clock::now();
		double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
		student.update_day(days_passed);
		teacher.update_day(days_passed);
		library.update_day(days_passed);

		if (valid_teacher) {  // If it is valid teacher, then call menu from teacher
			auto start = std::chrono::steady_clock::now();
			do {
				proceed = teacher.menu(library);
				reader = &teacher;
	  		    reader->printInfo();
				reader->get_copies();
				reader->get_period();

			} while (proceed);
			auto end = std::chrono::steady_clock::now();
			double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
			student.update_day(days_passed);
		}
		
		if (valid_student) {  // If it is valid student, then call menu from teacher
			auto start = std::chrono::steady_clock::now();
			do {
				proceed = student.menu(library);
				//student print 
			reader = &student;
	  		reader->printInfo();
			reader->get_copies();
				reader->get_period();
//          ^^^ make a pointer to the student object EQUAL to the base class pointer. Then use that to call the base function.
			} while (proceed);
			auto end = std::chrono::steady_clock::now();
			double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
			teacher.update_day(days_passed);
		}

		if (valid_librarian) {  // If it is valid librarian, then call menu from librarian
			auto start = std::chrono::steady_clock::now();
			do {
				proceed = librarian.menu(library, student, teacher);
			} while (proceed);
			auto end = std::chrono::steady_clock::now();
			double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
			teacher.update_day(days_passed);
		}
	}
	return 0;
}