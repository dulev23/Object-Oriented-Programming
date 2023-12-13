#include <iostream>

#include <cstring>

using namespace std;


class SpaceObject {
private:
    char name[100]{};
    char type[100]{};
    int distanceFromEarth;
public:
    SpaceObject(char *nam = "", char *ty = "", int dFE = 0) {
        strcpy(name, nam);
        strcpy(type, ty);
        distanceFromEarth = dFE;
    }

    ~SpaceObject() {
    }

    SpaceObject(const SpaceObject &SpaceObject) {
        strcpy(name, SpaceObject.name);
        strcpy(type, SpaceObject.type);
        distanceFromEarth = SpaceObject.distanceFromEarth;
    }

    int get_distanceFromEarth() {
        return distanceFromEarth;
    }

    char *get_name() {
        return name;
    }

    char *get_type() {
        return type;
    }

    void print() {
        cout << get_name() << " " << " (" << get_type() << ") - distance: " << distanceFromEarth
             << " light years away from Earth";
    }
};

class Alien {
private:
    char name[100]{};
    int age;
    char homePlanet[100]{};
    int numObj;
    SpaceObject spaceObjects[100];
public:
    Alien(char *_n = "Zorblax", int ag = 0, char *hP = "Xarkon", int NumObj = 0, SpaceObject *_spO = {}) {
        strcpy(name, _n);
        age = ag;
        strcpy(homePlanet, hP);
        numObj = NumObj;
        for (int i = 0; i < numObj; ++i) {
            spaceObjects[i] = _spO[i];
        }
    }

    ~Alien() {
    }

    Alien(const Alien &alien) {
        strcpy(name, alien.name);
        age = alien.age;
        strcpy(homePlanet, alien.homePlanet);
        numObj = alien.numObj;
        for (int i = 0; i < alien.numObj; ++i) {
            spaceObjects[i] = alien.spaceObjects[i];
        }
    }

    SpaceObject getObjectClosestToEarth() {
        SpaceObject closestObject = spaceObjects[0];
        for (int i = 1; i < numObj; ++i) {
            if (spaceObjects[i].get_distanceFromEarth() < closestObject.get_distanceFromEarth()) {
                closestObject = spaceObjects[i];
            }
        }
        return closestObject;
    }

    char *get_name() {
        return name;
    }

    int get_age() {
        return age;
    }

    char *get_homePlanet() {
        return homePlanet;
    }

    void print() {
        cout << "Alien name: " << get_name() << endl;
        cout << "Alien age: " << get_age() << endl;
        cout << "Alien home planet: " << get_homePlanet() << endl;
        cout << "Favourite space object closest to earth: " << "";
        getObjectClosestToEarth().print();
    }

};

int main() {
    char name[100], homePlanet[100];
    int age, numObj;
    cin >> name >> age >> homePlanet >> numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for (int i = 0; i < numObj; i++) {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin >> spaceObjectName >> spaceObjectType >> distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i] = SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien = Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}