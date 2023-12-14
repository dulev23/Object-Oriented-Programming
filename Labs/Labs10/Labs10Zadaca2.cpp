#include <iostream>
#include <cstring>

using namespace std;

class InvalidTimeException {
public:
    void print() {
        cout << "The time is not valid" << endl;
    }
};

class Race {
protected:
    char ime[40];
    int godOdr;
    int mesOdr;
    float vremeSek;
    float km;
public:
    Race() {
        strcpy(ime, "");
        godOdr = 0;
        mesOdr = 0;
        vremeSek = 0.0;
        km = 0.0;
    }

    Race(char *ime, int godOdr, int mesOdr, float vremeSek, float km) {
        strcpy(this->ime, ime);
        this->godOdr = godOdr;
        this->mesOdr = mesOdr;
        this->vremeSek = vremeSek;
        this->km = km;
    }

    virtual float heaviness() const {
        return (float) vremeSek / km;
    }

    friend ostream &operator<<(ostream &os, const Race &race) {
        os << race.ime << " " << race.mesOdr << "." << race.godOdr << " " << race.heaviness() << endl;
        return os;
    }

    float getVreme() {
        return vremeSek;
    }
};

class CarRace : public Race {
    float *pripremi;
    int brEl;
    int krugovi;
    static float CAR_COEF;
public:
    CarRace(char *ime = "", int godOdr = 0, int mesOdr = 0, float vremeSek = 0, float km = 0) : Race(ime, godOdr,
                                                                                                     mesOdr, vremeSek,
                                                                                                     km) {
        pripremi = new float[0];
        brEl = krugovi = 0;
    }

    CarRace(char *ime, int godOdr, int mesOdr, float vremeSek, float km, float *pripremi, int brEl, int krugovi) : Race(
            ime, godOdr, mesOdr, vremeSek, km) {
        this->brEl = brEl;
        this->pripremi = new float[brEl];
        for (int i = 0; i < brEl; i++) {
            this->pripremi[i] = pripremi[i];
        }
        this->krugovi = krugovi;

    }

    CarRace(const CarRace &c) {
        this->brEl = c.brEl;
        this->pripremi = new float[c.brEl];
        for (int i = 0; i < c.brEl; i++) {
            this->pripremi[i] = c.pripremi[i];
        }
        this->krugovi = c.krugovi;
    }

    CarRace &operator=(const CarRace &c) {
        if (this != &c) {
            delete[] pripremi;
            this->brEl = c.brEl;
            this->pripremi = new float[c.brEl];
            for (int i = 0; i < c.brEl; i++) {
                this->pripremi[i] = c.pripremi[i];
            }
            this->krugovi = c.krugovi;
        }
        return *this;
    }

    void setNumberLaps(int k) {
        krugovi = k;
    }

    float heaviness() const {
        float najdobrVr = 0;
        for (int i = 0; i < brEl; i++) {
            najdobrVr += pripremi[i];
        }

        float averageBestTime = (najdobrVr / (float) brEl);
        float heavy = Race::heaviness() + (averageBestTime * CAR_COEF);

        if (krugovi > 15) {
            return (float) heavy * 1.1;
        } else {
            return heavy;
        }
    }

    CarRace &operator+=(float p) {
        if (p < 10) {
            throw InvalidTimeException();
        }

        float *tmp = new float[brEl + 1];
        for (int i = 0; i < brEl; i++) {
            tmp[i] = pripremi[i];
        }
        tmp[brEl++] = p;
        delete[] pripremi;
        pripremi = tmp;
        return *this;
    }

    static void setKoeficient(float k) {
        CAR_COEF = k;
    }

    ~CarRace() {
        delete[] pripremi;
    }
};

float CarRace::CAR_COEF = 0.3;

int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            CarRace *nn = dynamic_cast<CarRace *>(niza[i]);
            if (nn != 0) {
                flag = 0;
                try {
                    (*nn) += best;
                    break;
                }
                catch (InvalidTimeException &e) {
                    e.print();
                }

            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1, vreme2;
        cin >> vreme1 >> vreme2;
        try {
            mgt += vreme1;
            mgt += vreme2;
        }
        catch (InvalidTimeException &e) {
            e.print();
        }

        cout << mgt;
    }

    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    return 0;
}