#include<iostream>
#include<cstring>

using namespace std;

enum Tip {
    LINUX,
    UNIX,
    WINDOWS
};

class OperativenSistem {
private:
    char *name;
    float version;
    Tip type;
    float size;
public:
    OperativenSistem() {
        name = nullptr;
        version = 0.0;
        type = WINDOWS;
        size = 0.0;
    }

    OperativenSistem(char *name, float version, Tip type, float size) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->version = version;
        this->type = type;
        this->size = size;
    }

    OperativenSistem(const OperativenSistem &OS) {
        name = new char[strlen(OS.name) + 1];
        strcpy(name, OS.name);
        version = OS.version;
        type = OS.type;
        size = OS.size;
    }

    ~OperativenSistem() {
        delete[]name;
    }

    OperativenSistem &operator=(const OperativenSistem &OS) {
        if (this != &OS) {
            delete[]name;
            this->name = new char[strlen(OS.name) + 1];
            strcpy(this->name, OS.name);
            version = OS.version;
            type = OS.type;
            size = OS.size;
        }
        return *this;
    }

    void pecati() {
        cout << "Ime: " << name << " Verzija: " << version << " Tip: " << type << " Golemina:" << size << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        return (strcmp(name, os.name) == 0 && (version == os.version) && (type == os.type) && (size == os.size));
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (version == os.version) {
            return 0;
        } else if (os.version > version) {
            return -1;
        } else {
            return 1;
        }
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        return (strcmp(name, sporedba.name) == 0) && (type == sporedba.type);
    }

    friend class Repozitorium;
};

class Repozitorium {
private:
    char name[20];
    OperativenSistem *OpSistem;
    int numOfOS;
public:
    Repozitorium(const char *ime) {
        strcpy(name, ime);
        OpSistem = nullptr;
        numOfOS = 0;
    }

    ~Repozitorium() {
        delete[]OpSistem;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < numOfOS; ++i) {
            OpSistem[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int flag = 0;

        for (int i = 0; i < numOfOS; i++) {
            if (OpSistem[i].ednakviSe(operativenSistem)) {
                flag = 1;
            }
        }
        if (flag == 0) {
            return;
        }
        OperativenSistem *tmp = new OperativenSistem[numOfOS - 1];
        int j = 0;
        for (int i = 0; i < numOfOS; i++) {
            if (!OpSistem[i].ednakviSe(operativenSistem)) {
                tmp[j] = OpSistem[i];
                j++;
            }
        }
        numOfOS--;
        delete[]OpSistem;
        OpSistem = tmp;
    }

    void dodadi(const OperativenSistem &nov) {
        for (int i = 0; i < numOfOS; i++) {
            if (OpSistem[i].istaFamilija(nov)) {
                if (OpSistem[i].sporediVerzija(nov) == -1) {
                    OpSistem[i] = nov;
                    return;
                }
            }
        }
        OperativenSistem *tmp = new OperativenSistem[numOfOS + 1];
        for (int i = 0; i < numOfOS; i++) {
            tmp[i] = OpSistem[i];
        }
        tmp[numOfOS++] = nov;
        delete[]OpSistem;
        OpSistem = tmp;
    }
};


int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}