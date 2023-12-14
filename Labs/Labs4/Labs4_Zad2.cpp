#include<iostream>
#include<cstring>

using namespace std;

class Student {
private:
    char *name;
    int age;
    char *major;
public:
    Student(const char *name = "", int a = 0, const char *major = "") {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        age = a;
        this->major = new char[strlen(major) + 1];
        strcpy(this->major, major);
    }

    Student(const Student &s) {
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        age = s.age;
        this->major = new char[strlen(s.major) + 1];
        strcpy(this->major, s.major);
    }

    int getAge() const {
        return age;
    }

    const char *getMajor() const {
        return major;
    }

    const char *getName() const {
        return name;
    }

    friend class Classroom;
};

class Classroom {
private:
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(int num = 0, int cap = 0) {
        students = new Student[cap];
        this->numStudents = num;
        this->capacity = cap;
    }

    Classroom(const Classroom &classroom) {
        students = new Student[classroom.capacity];
        for (int i = 0; i < classroom.numStudents; i++) {
            students[i] = classroom.students[i];
        }
        this->numStudents = classroom.numStudents;
        this->capacity = classroom.capacity;
    }

    void add(const Student &s) {
        if (numStudents >= capacity) {
            return;
        } else {
            students[numStudents] = s;
            numStudents++;
        }
    }

    void remove(const char *name) {
        int index = -1;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].getName(), name) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        for (int i = index; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        numStudents--;
    }

    ~Classroom() {
        delete[] students;
    }

    int getNumberOfStudents() const {
        return numStudents;
    }

    const Student *getStudents() const {
        return students;
    }

    void printStudents() const {
        for (int i = 0; i < numStudents; i++) {
            cout << students[i].getName() << "(" << students[i].getAge() << "," << " " << students[i].getMajor() << ")"
                 << endl;
        }
    }

    friend class Student;
};

double findMedianAge(const Classroom &classroom) {
    const Student *students = classroom.getStudents();
    int n = classroom.getNumberOfStudents() / 2;
    double median = students[n].getAge();

    if (classroom.getNumberOfStudents() % 2 == 0)
        median = (students[n].getAge() + students[n - 1].getAge()) / 2.0;

    return median;
}

int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i * numStudents + j] = student;
        }
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }

    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;

    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }

    return 0;
}