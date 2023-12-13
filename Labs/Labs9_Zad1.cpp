#include<iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char name[50]{};
    int age;
public:
    Employee(char *name = "", int age = 0) {
        strcpy(this->name, name);
        this->age = age;
    }

    virtual void displayInfo() = 0;
};

class Payable {
protected:
    double salary;
public:
    Payable(double salary = 0.0) {
        this->salary = salary;
    }

    virtual double calculateSalary() = 0;

};

class Developer : public Employee, public Payable {
private:
    char language[50]{};
public:
    Developer(char *name = "", int age = 0, double salary = 0.0, char *language = "") : Employee(name, age),
                                                                                        Payable(salary) {
        strcpy(this->language, language);
    }

    void displayInfo() {
        cout << "-- Developer Information --" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Programming language: " << language << endl;
    }

    double calculateSalary() {
        double totalSalary;
        totalSalary = salary - (0.1 * salary);
        return totalSalary;
    }
};

class Manager : public Employee, public Payable {
private:
    int departments;
public:
    Manager(char *name = "", int age = 0, double salary = 0.0, int departments = 0) : Employee(name, age),
                                                                                      Payable(salary) {
        this->departments = departments;
    }

    void displayInfo() {
        cout << "-- Manager Information --" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Number of Departments: " << departments << endl;
    }

    double calculateSalary() {
        double totalSalary;
        totalSalary = salary + ((salary * 0.05) * departments);
        return totalSalary;
    }
};

double biggestSalary(Payable *payable[5], int n) {
    double maxPlata = 0;
    for (int i = 0; i < n; ++i) {
        if (payable[i]->calculateSalary() > maxPlata) {
            maxPlata = payable[i]->calculateSalary();
        }
    }
    return maxPlata;
}

int main() {
    Payable *payable[5];
    Developer developers[5];
    Manager managers[5];
    int j = 0, k = 0;
    for (int i = 0; i < 5; i++) {
        char name[50];
        int age;
        double salary;
        cin >> name >> age >> salary;
        if (i % 2 == 0) {
            char programmingLanguage[50];
            cin >> programmingLanguage;
            developers[j] = Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i] = &developers[j];
            j++;
        } else {
            int numberOfDepartments;
            cin >> numberOfDepartments;
            managers[k] = Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i] = &managers[k];
            k++;
        }
    }
    cout << endl << "Biggest Salary: " << biggestSalary(payable, 5);
    return 0;
}