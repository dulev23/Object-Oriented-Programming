#include<iostream>
#include<cstring>

using namespace std;

class Vozac {
protected:
    char name[100]{};
    int age;
    int numRaces;
    bool veteran;
public:
    Vozac(char *_name = nullptr, int _age = 0, int _numRaces = 0, bool _veteran = false) {
        strcpy(name, _name);
        age = _age;
        numRaces = _numRaces;
        veteran = _veteran;
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.name << endl;
        os << vozac.age << endl;
        os << vozac.numRaces << endl;
        if (vozac.veteran == true) {
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual double EarningPerRace() = 0;

    virtual double danok() = 0;

};

class Avtomobilist : public Vozac {
private:
    double carPrice;
public:
    Avtomobilist(char *_name = nullptr, int _age = 0, int _numRaces = 0, bool _veteran = false, double _carPrice = 0.0)
            : Vozac(_name, _age, _numRaces, _veteran) {
        carPrice = _carPrice;
    }

    double EarningPerRace() {
        return carPrice / 5;
    }

    double danok() {
        double procent1 = 0.15, procent2 = 0.1;
        if (numRaces > 10) {
            return (EarningPerRace() * procent1);
        } else {
            return (EarningPerRace() * procent2);
        }
    }

};

class Motociklist : public Vozac {
private:
    int motorPower;
public:
    Motociklist(char *_name = nullptr, int _age = 0, int _numRaces = 0, bool _veteran = false, int _motorPower = 0)
            : Vozac(_name, _age, _numRaces, _veteran) {
        motorPower = _motorPower;
    }

    double EarningPerRace() {
        return motorPower * 20;
    }

    double danok() {
        if (veteran == true) {
            return EarningPerRace() * 0.25;
        } else {
            return EarningPerRace() * 0.2;
        }
    }
};

double soIstaZarabotuvachka(Vozac **pVozac, int n, Vozac *VozacX) {
    double counter;
    for (int i = 0; i < n; ++i) {
        if (pVozac[i]->EarningPerRace() == VozacX->EarningPerRace()) {
            counter++;
            i++;
        } else {
            counter = 0;
        }
    }
    return counter;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}