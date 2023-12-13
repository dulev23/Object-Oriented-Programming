#include<iostream>
#include<cstring>

using namespace std;

class Koncert {
private:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    double price;
    bool isElektronski;
public:
    Koncert(char *_naziv = "", char *_lokacija = "", double _cena = 0.0, bool _isElektronski = false) {
        strcpy(naziv, _naziv);
        strcpy(lokacija, _lokacija);
        price = _cena;
        isElektronski = _isElektronski;
    }

    virtual double cena() {
        return price * (1 - sezonskiPopust);
    }

    const char *getNaziv() const {
        return naziv;
    }

    virtual void setSezonskiPopust(float popust) {
        Koncert::sezonskiPopust = popust;
    }

    float getSezonskiPopust() {
        return sezonskiPopust;
    }

    bool isElektronskiKoncert() {
        return isElektronski;
    }

};

class ElektronskiKoncert : public Koncert {
private:
    char *DJname;
    float vremetraenje;
    bool zabava;
public:
    ElektronskiKoncert(char *_naziv = "", char *_lokacija = "", double _cena = 0.0, char *_DJName = "",
                       float _vremetraenje = 0.0, bool _zabava = false) : Koncert(_naziv, _lokacija, _cena) {
        DJname = new char[strlen(_DJName) + 1];
        vremetraenje = _vremetraenje;
        zabava = _zabava;
    }

    ElektronskiKoncert(const ElektronskiKoncert &ek) : Koncert(ek) {
        DJname = new char[strlen(ek.DJname) + 1];
        strcpy(DJname, ek.DJname);
        vremetraenje = ek.vremetraenje;
        zabava = ek.zabava;
    }

    virtual ~ElektronskiKoncert() {
        delete[]DJname;
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &ek) {
        if (this != &ek) {
            delete[]DJname;
            DJname = new char[strlen(ek.DJname) + 1];
            strcpy(DJname, ek.DJname);
            vremetraenje = ek.vremetraenje;
            zabava = ek.zabava;
        }
        return *this;
    }

    float getSezonskiPopust() {
        return Koncert::getSezonskiPopust();
    }

    double cena() {
        double osnovnaCena = Koncert::cena();

        if (vremetraenje > 7) {
            osnovnaCena += 360;
        } else if (vremetraenje > 5) {
            osnovnaCena += 150;
        }
        if (zabava) {
            osnovnaCena -= 50;
        } else {
            osnovnaCena += 100;
        }

        return osnovnaCena;
    }

};

float Koncert::sezonskiPopust = 0.2;

void najskapKoncert(Koncert **koncerti, int n) {
    double maxPrice = koncerti[0]->cena();
    int maxIndex = 0;
    int elektronskiCount = 0;

    for (int i = 0; i < n; i++) {
        double price = koncerti[i]->cena();
        if (price > maxPrice) {
            maxPrice = price;
            maxIndex = i;
        }
        if (dynamic_cast<ElektronskiKoncert *>(koncerti[i])) {
            elektronskiCount++;
        }
    }

    cout << "Najskap koncert: " << koncerti[maxIndex]->getNaziv() << " " << koncerti[maxIndex]->cena() << endl;
    cout << "Elektronski koncerti: " << elektronskiCount << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert **koncerti, int n, const char *naziv, bool elektronski) {
    for (int i = 0; i < n; i++) {
        if (koncerti[i]->isElektronskiKoncert() == elektronski && strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
            cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
            return true;
        }
    }
    return false;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}