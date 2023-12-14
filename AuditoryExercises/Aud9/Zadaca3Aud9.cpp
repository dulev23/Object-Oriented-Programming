#include<iostream>
#include<cstring>

using namespace std;

class Shape {
protected:
    double height;
    double base;
public:
    Shape(double height, double base) {
        this->height = height;
        this->base = base;
    }

    virtual void print() = 0;

    virtual double volume() = 0;

    double getHeight() const {
        return height;
    }
};

class Cylinder : public Shape {
public:
    Cylinder(double height, double base) : Shape(height, base) {}

    double volume() {
        return base * base * 3.14 * height;
    }

    void print() {
        cout << "Cylinder with volume: " << volume();
    }
};

class Cone : public Shape {
public:
    Cone(double height, double base) : Shape(height, base) {}

    double volume() {
        return 1.0 / 3 * base * base * height * 3.14;
    }

    void print() {
        cout << "Cone with volume: " << volume();
    }
};

class Cuboid : public Shape {
private:
    double secondBase;
public:
    Cuboid(double height, double base, double secondBase) : Shape(height, base) {
        this->secondBase = secondBase;
    }

    double volume() {
        return base * secondBase * height;
    }

    void print() {
        cout << "Cuboid with volume: " << volume();
    }
};

int countShapesWithoutCircleBase(Shape **shapes, int n) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        Cuboid *castedCuboid = dynamic_cast<Cuboid *>(shapes[i]);
        if (castedCuboid == 0) {
            ++counter;
        }
    }
    return counter;
}

void shapeWithLargestVolume(Shape **shapes, int n) {
    Shape *max = shapes[0];
    for (int i = 0; i < n; ++i) {
        if (shapes[i]->volume() > max->volume()) {
            max = shapes[i];
        }
    }
    max->print();
}

int main() {
    Shape *s = new Cuboid(10, 5, 10);
    s->print();

    int n;
    cin >> n;

    Shape **shapes = new Shape *[n];
    for (int i = 0; i < n; ++i) {
        int type; //1=cylinder, 2=cone, 3=cuboid
        double height, base, secondBase;
        cin >> type >> height >> base;
        if (type == 1) { //cylinder
            shapes[i] = new Cylinder(height, base);
        } else if (type == 2) { //cone
            shapes[i] = new Cone(height, base);
        } else { //cuboid
            cin >> secondBase;
            shapes[i] = new Cuboid(height, base, secondBase);
        }
        shapes[i]->print();
    }

    shapeWithLargestVolume(shapes, n);
    cout << endl << "Number of shapes without a circle base is: " << countShapesWithoutCircleBase(shapes, n);
    return 0;
}