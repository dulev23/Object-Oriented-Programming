#include <iostream>
#include <cstring>

using namespace std;

// vashiot kod ovde

class FudbalskaEkipa {
protected:
    char name[100]{};
    int goals[10]{};
public:
    FudbalskaEkipa(const char *_name = "", const int *_goals = nullptr) {
        strcpy(name, _name);
        for (int i = 0; i < 10; ++i) {
            goals[i] = _goals[i];
        }
    }

    FudbalskaEkipa &operator+=(int goal) {
        for (int i = 0; i < 10; ++i) {
            goals[i] = goals[i + 1];
        }
        goals[9] = goal;
        return *this;
    }

    ~FudbalskaEkipa() {}

    virtual int uspeh() const = 0;

    bool operator>(const FudbalskaEkipa &fe) const {
        return uspeh() > fe.uspeh();
    }

    virtual const char *getName() const = 0;

    friend ostream &operator<<(ostream &os, const FudbalskaEkipa &ekipa) {
        os << ekipa.getName() << endl;
        os << ekipa.name << endl;
        os << ekipa.uspeh() << endl;
        return os;
    }

};

class Klub : public FudbalskaEkipa {
private:
    char clubName[50]{};
    int numTitles;
public:
    Klub(const char *_name = "", const int *_goals = nullptr, const char *_ime = "", const int _numTitles = 0)
            : FudbalskaEkipa(_name, _goals) {
        strcpy(clubName, _ime);
        numTitles = _numTitles;
    }

    int uspeh() const {
        int total = 0;
        for (int i = 0; i < 10; ++i) {
            total += (goals[i] * 3) + (numTitles * 100);
        }
        return total;
    }

    const char *getName() const {
        return clubName;
    }

};

class Reprezentacija : public FudbalskaEkipa {
private:
    char country[50];
    int appearances;
public:
    Reprezentacija(const char *_name = "", const int *_goals = nullptr, const char *_country = "",
                   const int _appearances = 0) : FudbalskaEkipa(_name, _goals), country(), appearances(_appearances) {
        strcpy(country, _country);
        appearances = _appearances;
    }

    int uspeh() const {
        int total = 0;
        for (int i = 0; i < 10; ++i) {
            total += (goals[i] * 3) + (appearances * 5);
        }
        return total;
    }

    const char *getName() const {
        return country;
    }

};

void najdobarTrener(FudbalskaEkipa **fudbalskaEkipa, int n) {
    FudbalskaEkipa *tmp = fudbalskaEkipa[0];
    for (int i = 0; i < n; ++i) {
        if (tmp->uspeh() < fudbalskaEkipa[i]->uspeh()) {
            tmp = fudbalskaEkipa[i];
        }
    }
    cout << *tmp;
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}