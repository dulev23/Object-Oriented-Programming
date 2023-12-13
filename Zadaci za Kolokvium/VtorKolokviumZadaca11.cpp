#include<iostream>
#include<cstring>

using namespace std;

//место за вашиот код
class Delo {
private:
    char ime[50]{};
    int godina;
    char zemja[50]{};
public:
    Delo(char *_ime = "", int _godina = 0, char *_zemja = "") {
        strcpy(ime, _ime);
        godina = _godina;
        strcpy(zemja, _zemja);
    }

    const char *getIme() const {
        return ime;
    }

    bool operator==(const Delo &other) const {
        return strcmp(ime, other.ime) == 0;
    }

    int getGodina() const {
        return godina;
    }

    const char *getZemja() const {
        return zemja;
    }

};

class Pretstava {
protected:
    Delo delo;
    int karti;
    char data[15]{};
public:
    Pretstava(Delo d, int _karti = 0, char *_data = "") {
        delo = d;
        karti = _karti;
        strcpy(data, _data);
    }

    const Delo &getDelo() const {
        return delo;
    }

    int getKarti() const {
        return karti;
    }

    virtual double cena() {
        int N, M;
        if (delo.getGodina() >= 1901 && delo.getGodina() <= 2100) {
            M = 50;
        } else if (delo.getGodina() >= 1801 && delo.getGodina() < 1901) {
            M = 75;
        } else {
            M = 100;
        }

        if (strcmp(delo.getZemja(), "Italija") == 0) {
            N = 100;
        } else if (strcmp(delo.getZemja(), "Rusija") == 0) {
            N = 150;
        } else {
            N = 80;
        }
        return N + M;
    }

};

class Opera : public Pretstava {
public:
    Opera(const Delo &d, int _karti = 0, char *_data = "") : Pretstava(d, _karti, _data) {

    }

};

class Balet : public Pretstava {
protected:
    static double Cena;
public:
    Balet(const Delo &d, int _karti = 0, char *_data = "") : Pretstava(d, _karti, _data) {

    }

    static void setCenaBalet(int cena) {
        Balet::Cena = cena;
    }

    virtual double cena() {
        return Pretstava::cena() + Balet::Cena;
    }

};

double Balet::Cena = 150;


//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int prihod(Pretstava **pretstavi, int n) {
    int vkupenPrihod = 0;
    for (int i = 0; i < n; i++) {
        vkupenPrihod += pretstavi[i]->cena() * pretstavi[i]->getKarti();
    }
    return vkupenPrihod;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo d) {
    int broj = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(pretstavi[i]->getDelo().getIme(), d.getIme()) == 0) {
            broj++;
        }
    }
    return broj;
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}