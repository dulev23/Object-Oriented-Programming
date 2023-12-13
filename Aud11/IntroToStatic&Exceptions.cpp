#include<iostream>
#include<cstring>

using namespace std;

class NotValidUsernameException {
private:
    char notValidUsername[50];
public:
    NotValidUsernameException(char *email = "test@test.com") {
        strcpy(notValidUsername, email);
    }

    void showMessage() {
        cout << notValidUsername << " is not valid! Try again!" << endl;
    }

};

class User {
protected:
    int id;
    char username[50];
    static int ID_TRACKER; //static clen
public:
    User(char *username = "test") {
        bool atSignFound = false;
        bool dotSignFound = false;
        for (int i = 0; i < strlen(username); ++i) {
            if (username[i] == '@') {
                atSignFound = true;
            }
            if (atSignFound) {
                if (username[i] == '.') {
                    dotSignFound = true;
                }
            }
        }

        if (!atSignFound || !dotSignFound) {
            throw NotValidUsernameException(username);
        }

        strcpy(this->username, username);
        this->id = ID_TRACKER++;
    }

    void print() {
        cout << id << " " << username << endl;
    }
};

int User::ID_TRACKER = 1; //se inicijalizira nadvor od klasata

int main() {
    try {
        User u1("Stefan@gmail.com"); //ID=1
        u1.print();
        User u2("Trajce@gmail.com"); //ID=2
        u2.print();
        User u3("Petko"); //ID=3
        u3.print();
    }

    catch (NotValidUsernameException e) {
        e.showMessage();
    }

    return 0;
}