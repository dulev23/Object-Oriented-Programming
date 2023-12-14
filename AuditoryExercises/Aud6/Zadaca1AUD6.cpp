#include<iostream>
#include<cstring>

using namespace std;

class Team {
private:
    char *name;
    char *stadium;
    char *city;
public:
    Team(const char *name = "", const char *stadium = "", const char *city = "") {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->stadium = new char[strlen(stadium) + 1];
        strcpy(this->stadium, stadium);
        this->city = new char[strlen(city) + 1];
        strcpy(this->city, city);
    }

    Team(const Team &t) {
        this->name = new char[strlen(t.name) + 1];
        strcpy(this->name, t.name);
        this->stadium = new char[strlen(t.stadium) + 1];
        strcpy(this->stadium, t.stadium);
        this->city = new char[strlen(t.city) + 1];
        strcpy(this->city, t.city);
    }

    Team &operator=(const Team &other) {
        if (this != &other) {
            delete[] name;
            delete[] stadium;
            delete[] city;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->stadium = new char[strlen(other.stadium) + 1];
            strcpy(this->stadium, other.stadium);
            this->city = new char[strlen(other.city) + 1];
            strcpy(this->city, other.city);
        }
        return *this;
    }

    ~Team() {
        delete[] name;
        delete[] stadium;
        delete[] city;
    }

    void print() {
        cout << "Team name: " << name << endl;
        cout << "Stadium: " << stadium << endl;
        cout << "City: " << city << endl;
    }
};

int main() {
    int n;
    cin >> n;
    Team *teams = new Team[n];
    char name[100];
    char stadium[100];
    char city[100];
    for (int i = 0; i < n; ++i) {
        cin >> name >> stadium >> city;
        teams[i] = Team(name, stadium, city);
    }

    for (int i = 0; i < n; i++) {
        teams[i].print();
    }
    return 0;
}