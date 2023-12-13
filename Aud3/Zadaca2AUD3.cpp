#include<iostream>
#include<cstring>

using namespace std;

enum Type {
    employee, //0
    manager,  //1
    owner     //2
};

class Employee {
private:
    char name[50];
    int salary;
    Type type;
public:
    Employee(char *_name = "Nikola", int _salary = 30000, Type _type = employee) {
        strcpy(name, _name);
        salary = _salary;
        type = _type;
    }

    ~Employee() {
        //vo ovaa situacija ne pisuvame ovde nisto
    }

    //prv nacin na pecatenje
    void print() {
        cout << "Employee: " << name << " Salary: " << salary << " Type: ";
        switch (type) {
            case employee:
                cout << "Basic" << endl;
                break;
            case manager:
                cout << "Manager" << endl;
                break;
            case owner:
                cout << "Owner" << endl;
                break;
        }
    }

    //Vtor nacin na pecatenje
//    void setName(char _name[50]){
//        strcpy(name,_name);
//    }
//
//    void setSalary(int _salary){
//        salary=_salary;
//    }
//
//    void setType(Type _type){
//        type=_type;
//    }

    int compareTo(Employee other) {
        int diff = salary - other.salary;
        if (diff == 0) {
            return diff;
        } else if (diff > 0) {
            return 1;
        } else {
            return -1;
        }
    }
};

void swap(Employee &e1, Employee &e2) {
    Employee tmp = e1;
    e1 = e2;
    e2 = tmp;
}

int main() {
    int n;
    cin >> n;
    Employee employees[50];
    char name[50];
    int salary;
    int type;
    for (int i = 0; i < n; ++i) {
        cin >> name >> salary >> type; //Nikola 30000 0
        employees[i] = Employee(name, salary, (Type) type);
//        employees[i].setName(name);
//        employees[i].setSalary(salary);
//        employees[i].setType((Type)type);
    }

    //TODO sort employees by salary in descending order

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (employees[j].compareTo(employees[j + 1]) == -1)
                swap(employees[j], employees[j + 1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        employees[i].print();
    }
    return 0;
}