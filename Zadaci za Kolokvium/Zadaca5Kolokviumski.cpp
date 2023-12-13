#include<iostream>
#include<cstring>

using namespace std;

class Gitara {
private:
    char serialNumber[25];
    double price;
    int CreateDate;
    char type[40];
public:
    Gitara(char *t = "", char *sN = "", int cDate = 0, double p = 0.0) {
        strcpy(type, t);
        strcpy(serialNumber, sN);
        CreateDate = cDate;
        price = p;
    }

    Gitara(const Gitara &g) {
        strcpy(this->type, g.type);
        strcpy(this->serialNumber, g.serialNumber);
        this->CreateDate = g.CreateDate;
        this->price = g.price;
    }

    Gitara &operator=(const Gitara &g) {
        if (this != &g) {
            strcpy(this->type, g.type);
            strcpy(this->serialNumber, g.serialNumber);
            this->CreateDate = g.CreateDate;
            this->price = g.price;
        }
        return *this;
    }

    ~Gitara() {
    }

    bool daliIsti(Gitara &g) {
        return strcmp(this->serialNumber, g.serialNumber) == 0;
    }

    void pecati() {
        cout << serialNumber << " " << type << " " << price << endl;
    }

    double getNabavna() {
        return price;
    }

    char *getSeriski() {
        return serialNumber;
    }

    int getGodina() {
        return CreateDate;
    }

    char *getTip() {
        return type;
    }
};

class Magacin {
private:
    char location[60];
    char name[50];
    int openDate;
    Gitara *gitara;
    int numOfObjects;
public:
    Magacin(char *n = "", char *l = "", int oD = 0) {
        strcpy(name, n);
        strcpy(location, l);
        gitara = NULL;
        numOfObjects = 0;
        openDate = oD;
    }

    Magacin(const Magacin &m) {
        strcpy(location, m.location);
        strcpy(name, m.name);
        openDate = m.openDate;
        gitara = new Gitara[m.numOfObjects];
        for (int i = 0; i < m.numOfObjects; ++i) {
            gitara[i] = m.gitara[i];
        }
        numOfObjects = m.numOfObjects;
    }

    Magacin &operator=(const Magacin &m) {
        if (this != &m) {
            delete[] gitara;
            strcpy(location, m.location);
            strcpy(name, m.name);
            openDate = m.openDate;
            gitara = new Gitara[m.numOfObjects];
            for (int i = 0; i < m.numOfObjects; ++i) {
                gitara[i] = m.gitara[i];
            }
            numOfObjects = m.numOfObjects;
        }
        return *this;
    }

    ~Magacin() {
        delete[] gitara;
    }

    double vrednost() {
        double total = 0.0;
        for (int i = 0; i < numOfObjects; ++i)
            total += gitara[i].getNabavna();
        return total;
    }

    void dodadi(Gitara &g) {
        Gitara *gitara1 = new Gitara[numOfObjects + 1];
        for (int i = 0; i < numOfObjects; ++i) {
            gitara1[i] = gitara[i];
        }
        gitara1[numOfObjects++] = g;
        delete[] gitara;
        gitara = gitara1;
    }


    void prodadi(Gitara &g) {
        int newBr = 0;
        for (int i = 0; i < numOfObjects; ++i) {
            if (gitara[i].daliIsti(g) == false) {
                newBr++;
            }
        }
        Gitara *tmp = new Gitara[newBr];
        int j = 0;
        for (int i = 0; i < numOfObjects; i++) {
            if (gitara[i].daliIsti(g) == false) {
                tmp[j] = gitara[i];
                j++;
            }
        }
        delete[] gitara;
        gitara = tmp;
        numOfObjects = newBr;
    }

    void pecati(bool daliNovi) {
        cout << name << " " << location << endl;
        for (int i = 0; i < numOfObjects; ++i) {
            if (daliNovi == true && gitara[i].getGodina() > openDate) {
                gitara[i].pecati();
            } else if (daliNovi == false) {
                gitara[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
