

#include <iostream>

class Reader {

    public:
        virtual void printrole() {
            ;
        };
};

class Student : public Reader{
    private:

    public:
        void printrole(){
            std::cout << "Student.\n";
        };
};

class Teacher : public Reader{
    private:

    public:
        void printrole(){
            std::cout << "Teacher.\n";
        };
};

/*
void print_Role(Reader* reader){
    reader->printrole();
};
 */

int main(){
    Reader *readerbase;
    Student studentderived;
    readerbase = &studentderived;

    readerbase->printrole();

    Teacher t;
    readerbase = &t;
    readerbase->printrole();
};

