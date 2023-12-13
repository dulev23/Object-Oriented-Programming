#include<iostream>
#include<cstring>

using namespace std;

class String {
private:
    char *content; //dynamically allocated array of characters
public:
    //default constructor and constructor with argument
    //MUST: 1. copy constructor, 2. destructor, 3. operator=
    String(char *cptr = "") { //2in1 constructor
        this->content = new char[strlen(cptr) + 1];
        strcpy(this->content, cptr);
    }

    String(const String &s) { //copy constructor
        //1. allocate memory za this->content
        this->content = new char[strlen(s.content) + 1];
        //2.copy content
        strcpy(this->content, s.content);
    }

    ~String() {
        delete[] content;
    }

    String &operator=(const String &st) {
        if (this != &st) {
            delete[] content;
            this->content = new char[strlen(st.content) + 1];
            strcpy(this->content, st.content);
        }
        return *this;
    }
};

int main() {
    String string[10];
    return 0;
}