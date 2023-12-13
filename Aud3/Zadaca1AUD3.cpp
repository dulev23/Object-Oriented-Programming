#include<iostream>
#include<math.h>

using namespace std;

class Triangle {
private:
    int a, b, c;
public:
    Triangle(int _a = 5, int _b = 4, int _c = 3) {
        cout << "Constructor is called" << endl;
        a = _a;
        b = _b;
        c = _c;
    }

    ~Triangle() {
        cout << "Object is destroyed" << endl;
    }

    int perimeter() {
        return a + b + c;
    }

    float area() {
        float s = float(a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void print() {
        cout << "Triangle with sides: " << a << "," << b << "," << c << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
    }
};

int main() {
    Triangle t;
    t.print();
    return 0;
}