#include <iostream>
#include <cstring>

using namespace std;

class InvalidProductionDate {
private:
    char message[60];
public:
    InvalidProductionDate(char *_message = "") {
        strcpy(message, _message);
    }

    void showMessage() {
        cout << "Невалидна година на производство" << endl;
    }
};

enum tip {
    smartphone,
    computer
};

class Device {
protected:
    char model[100]{};
    tip type;
    static float proverka;
    int godina;
public:
    Device(char *_model = "Samsung", tip _type = computer, int _godina = 0) {
        strcpy(model, _model);
        type = _type;
        godina = _godina;
    }

    friend ostream &operator<<(ostream &os, const Device &device) {
        os << device.model << endl;
        float casoviZaProverka = proverka;
        if (device.godina > 2015) {
            casoviZaProverka += 2.0;
        }
        if (device.type == computer) {
            casoviZaProverka += 2.0;
        }
        switch (device.type) {
            case smartphone:
                os << "Mobilen ";
                break;
            case computer:
                os << "Laptop ";
                break;
        }
        os << casoviZaProverka << endl;
        return os;
    }

    static void setPocetniCasovi(float i) {
        Device::proverka = i;
    }

    int getGodina() const {
        return godina;
    }

};

float Device::proverka = 1.0;


class MobileServis {
private:
    char address[100]{};
    Device **devices;
    int numDevices;
public:
    MobileServis(const char *_address = "") {
        strcpy(address, _address);
        devices = nullptr;
        numDevices = 0;
    }

    MobileServis(const MobileServis &ms) {
        strcpy(address, ms.address);
        devices = new Device *[ms.numDevices];
        numDevices = ms.numDevices;
        for (int i = 0; i < ms.numDevices; ++i) {
            devices[i] = ms.devices[i];
        }
    }

    MobileServis &operator=(const MobileServis &ms) {
        if (this != &ms) {
            delete[]devices;
            strcpy(address, ms.address);
            devices = new Device *[ms.numDevices];
            numDevices = ms.numDevices;
            for (int i = 0; i < ms.numDevices; ++i) {
                devices[i] = ms.devices[i];
            }
        }
        return *this;
    }

    ~MobileServis() {
        delete[]devices;
    }

    MobileServis &operator+=(const Device &d) {
        if (d.getGodina() < 2000 || d.getGodina() > 2019) {
            throw InvalidProductionDate();
        }
        Device **newDevice = new Device *[numDevices + 1];
        for (int i = 0; i < numDevices; ++i) {
            newDevice[i] = devices[i];
        }

        newDevice[numDevices] = new Device(d);

        delete[]devices;
        devices = newDevice;
        numDevices++;
        return *this;
    }


    void pecatiCasovi() {
        cout << "Ime: " << address << endl;
        for (int i = 0; i < numDevices; ++i) {
            cout << *devices[i];
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &ipd) {
                ipd.showMessage();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &ipd) {
                ipd.showMessage();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);

            try {
                t += tmp;
            } catch (InvalidProductionDate &ipd) {
                ipd.showMessage();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);

            t += tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &ipd) {
                ipd.showMessage();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}