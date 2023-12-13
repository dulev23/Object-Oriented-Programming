#include<iostream>
#include<cstring>

using namespace std;

class MobilePhone {
private:
    char model[20];
    int modelNumber;
    int year;
public:
    MobilePhone(char *m = "Samsung", int mN = 22, int y = 2022) {
        strcpy(model, m);
        modelNumber = mN;
        year = y;
    }

    ~MobilePhone() {
    }

    MobilePhone(const MobilePhone &mobilePhone) {
        strcpy(model, mobilePhone.model);
        modelNumber = mobilePhone.modelNumber;
        year = mobilePhone.year;
    }

    void print() {
        cout << model << " " << modelNumber << " release year: " << year;
    }
};

class Owner {
private:
    char name[20];
    char surname[20];
    MobilePhone mobilePhone;
public:
    Owner(char *_name = "Marko", char *_surname = "Petrov", MobilePhone _mobilePhone = {}) {
        strcpy(name, _name);
        strcpy(surname, _surname);
        mobilePhone = _mobilePhone;
    }

    ~Owner() {
    }

    Owner(const Owner &owner) {
        strcpy(name, owner.name);
        strcpy(surname, owner.surname);
        mobilePhone = owner.mobilePhone;
    }

    void print() {
        cout << name << " " << surname << " has a mobile phone:" << endl;
        mobilePhone.print();
    }

};

int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin >> testCase;

    cin >> model;
    cin >> modelNumber;
    cin >> year;
    cin >> name;
    cin >> surname;

    if (testCase == 1) {
        MobilePhone mobilePhone(model, modelNumber, year);

        Owner owner(name, surname, mobilePhone);
        owner.print();
    }
    if (testCase == 2) {
        MobilePhone mobilePhone(MobilePhone(model, modelNumber, year));

        Owner owner(name, surname, mobilePhone);
        owner.print();
    }
    return 0;
}