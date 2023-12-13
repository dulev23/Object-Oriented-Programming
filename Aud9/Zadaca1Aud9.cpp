#include<iostream>
#include<cstring>

using namespace std;

class Animal {
protected:
    char name[30];
public:
    Animal(char *n) {
        strcpy(name, n);
    }

    virtual void makeSound() {
        cout << name << " is making the sound bla bla" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(char *name) : Animal(name) {

    }

    void makeSound() {
        cout << name << " is making the sound afafaf" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(char *name) : Animal(name) {

    }

    void makeSound() {
        cout << name << " is making the sound meow-meow" << endl;
    }
};

int main() {
//    Animal ** animals=new Animal * [3];
//
//    animals[0] = new Animal("Simba");
//    animals[1] = new Dog("Russell");
//    animals[2] = new Cat("Garfield");
//
//    for (int i = 0; i < 3; ++i) {
//        animals[i]->makeSound();
//    }

    int n;
    cin >> n;

    Animal **animals = new Animal *[n];
    for (int i = 0; i < n; ++i) {
        int type; //1=cat 2=dog
        char name[30];
        cin >> type >> name;
        if (type == 1) {
            animals[i] = new Cat(name);
        } else {
            animals[i] = new Dog(name);
        }
    }

    for (int i = 0; i < n; ++i) {
        animals[i]->makeSound();
    }
    return 0;
}