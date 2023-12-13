#include<iostream>
#include<cstring>

using namespace std;

enum tip {
    pop, rap, rock
};

class Pesna {
private:
    char *ime;
    double vremetraenje;
    tip type;
public:
    Pesna(const char *ime = "", double min = 20.0, enum tip type = rap) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->vremetraenje = min;
        this->type = type;
    }

    Pesna &operator=(const Pesna &p) {
        delete[] ime;
        this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);
        this->vremetraenje = p.vremetraenje;
        this->type = p.type;
    }

    Pesna(const Pesna &p) {
        this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);
        this->vremetraenje = p.vremetraenje;
        this->type = p.type;
    }

    ~Pesna() {
        delete[] ime;
    }

    void pecati() {
        cout << "\"" << getIme() << "\"-" << getVremetraenje() << "min" << endl;
    }

    char *getIme() {
        return ime;
    }

    int getVremetraenje() {
        return vremetraenje;
    }

    tip getTipPesna() {
        return type;
    }

    friend class CD;
};

class CD {
private:
    Pesna pesni[10];
    int brojPesni;
    int maxDuration;

public:
    CD(int maxDuration = 0) {
        brojPesni = 0;
        this->maxDuration = maxDuration;
    }

    CD(const CD &p) {
        this->brojPesni = p.brojPesni;
        this->maxDuration = p.maxDuration;
    }

    void dodadiPesna(Pesna p) {
        if (brojPesni < 10 && maxDuration - p.getVremetraenje() >= 0) {
            pesni[brojPesni++] = p;
            maxDuration -= p.getVremetraenje();
        }
    }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < brojPesni; i++) {
            if (pesni[i].getTipPesna() == t) {
                pesni[i].pecati();
            }
        }
    }

    Pesna &getPesna(int i) {
        return pesni[i];
    }

    int getBroj() {
        return brojPesni;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }

    return 0;
}