#include<iostream>
#include<cmath>

using namespace std;

class RoundPeg {
protected:
    float radius;
public:
    RoundPeg(float radius = 0.0) {
        this->radius = radius;
    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        this->radius = radius;
    }
};

class SquarePeg {
protected:
    float side;
public:
    SquarePeg(float side = 0.0) {
        this->side = side;
    }

    void setSide(float side) {
        this->side = side;
    }

    float getSide() const {
        return side;
    }

};

class SquarePegAdapter : public SquarePeg, public RoundPeg {
public:
    SquarePegAdapter(float side) : SquarePeg(), RoundPeg(side) {
    }

    int getRadius() const {
        return side * sqrt(2) / 2;
    }

};

class RoundHole {
    float radius;
public:
    RoundHole(float radius) {
        this->radius = radius;
    }

    void setRadius(float radius) {
        this->radius = radius;
    }

    float getRadius() const {
        return radius;
    }

    bool fits(RoundPeg *roundPeg) {
        return roundPeg->getRadius() <= this->radius;
    }
};

int main() {
    RoundHole hole(10);
    RoundPeg *peg1 = new RoundPeg(8);
    RoundPeg *peg2 = new RoundPeg(11);

    cout << hole.fits(peg1) << endl;
    cout << hole.fits(peg2) << endl;

    RoundPeg *peg3 = new SquarePegAdapter(20);
    cout << hole.fits(peg3) << endl;

    return 0;
}