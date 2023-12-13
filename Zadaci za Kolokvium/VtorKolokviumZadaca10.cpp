#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код

class NegativnaVrednost {
private:
    char poraka[100];
public:
    NegativnaVrednost(char *_poraka = "") {
        strcpy(poraka, _poraka);
    }

    void showMessage() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
protected:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(char *_naslov = "", char *_kategorija = "", char *_opis = "", float _cena = 0.0) {
        strcpy(naslov, _naslov);
        strcpy(kategorija, _kategorija);
        strcpy(opis, _opis);
        cena = _cena;
    }

    bool operator>(const Oglas &o) const {
        return cena > o.cena;
    }

    friend ostream &operator<<(ostream &os, const Oglas &oglas) {
        os << oglas.naslov << endl;
        os << oglas.opis << endl;
        os << oglas.cena << " evra" << endl;
        return os;
    }

    float getCena() const {
        return cena;
    }

    const char *getKategorija() const {
        return kategorija;
    }

};

class Oglasnik : public Oglas {
protected:
    char ime[20];
    Oglas *oglasi;
    int numOglasi;
public:
    Oglasnik(char *_ime = "", Oglas *_oglasi = nullptr, int _numOglasi = 0) {
        strcpy(ime, _ime);
        numOglasi = _numOglasi;
        oglasi = new Oglas[numOglasi];
        for (int i = 0; i < numOglasi; ++i) {
            oglasi[i] = _oglasi[i];
        }
    }

    Oglasnik(const Oglasnik &o) {
        strcpy(ime, o.ime);
        numOglasi = o.numOglasi;
        oglasi = new Oglas[numOglasi];
        for (int i = 0; i < numOglasi; ++i) {
            oglasi[i] = o.oglasi[i];
        }
    }

    Oglasnik &operator=(const Oglasnik &o) {
        if (this != &o) {
            delete[] oglasi;
            strcpy(ime, o.ime);
            numOglasi = o.numOglasi;
            oglasi = new Oglas[numOglasi];
            for (int i = 0; i < numOglasi; ++i) {
                oglasi[i] = o.oglasi[i];
            }
        }
        return *this;
    }

    ~Oglasnik() {
        delete[]oglasi;
    }

    Oglasnik &operator+=(const Oglas &o) {
        if (o.getCena() < 0) {
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
        }

        Oglas *newOglasi = new Oglas[numOglasi + 1];
        for (int i = 0; i < numOglasi; ++i) {
            newOglasi[i] = oglasi[i];
        }

        newOglasi[numOglasi] = o;
        delete[] oglasi;
        oglasi = newOglasi;
        ++numOglasi;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Oglasnik &oglasnik) {
        out << "FINKI-Oglasnik " << oglasnik.kategorija << std::endl;
        for (int i = 0; i < oglasnik.numOglasi; ++i) {
            out << oglasnik.oglasi[i] << std::endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < numOglasi; ++i) {
            if (strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout << oglasi[i] << endl;
            }
        }
    }

    void najniskaCena() {
        Oglas minimum = oglasi[0];
        for (int i = 1; i < numOglasi; ++i) {
            if (minimum.getCena() > oglasi[i].getCena()) {
                minimum = oglasi[i];
            }
        }
        cout << minimum << endl;
    }
};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
//            if(cena<0){
//                throw NegativnaVrednost();
//            }
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            } catch (NegativnaVrednost &nv) {
                nv.showMessage();
            }
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost &nv) {
                nv.showMessage();
            }
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost &nv) {
                nv.showMessage();
            }
        }
        cout << ogl;
    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            } catch (NegativnaVrednost &nv) {
                nv.showMessage();
            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}