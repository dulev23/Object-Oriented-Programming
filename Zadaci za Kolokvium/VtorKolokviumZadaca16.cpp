#include<iostream>
#include<cstring>

using namespace std;

class Transport {
protected:
    char destination[20];
    int price;
    int distance;
public:
    Transport(char *_destination = "", int _price = 0, int _distance = 0) {
        strcpy(destination, _destination);
        price = _price;
        distance = _distance;
    }

    virtual double Price() const = 0;

    bool operator<(const Transport &rhs) const {
        return distance < rhs.distance;
    }

    const char *getDestination() const {
        return destination;
    }

    int getDistance() const {
        return distance;
    }

};

class AvtomobilTransport : public Transport {
private:
    bool platenSofer;
public:
    AvtomobilTransport(char *_destination = "", int _price = 0, int _distance = 0, bool _platenSofer = true)
            : Transport(_destination, _price, _distance), platenSofer(_platenSofer) {
        platenSofer = _platenSofer;
    }

    double Price() const {
        if (platenSofer) {
            return price * 1.2;
        } else {
            return price;
        }
    }
};

class KombeTransport : public Transport {
private:
    int passengers;
public:
    KombeTransport(char *_destination = "", int _price = 0, int _distance = 0, int _passengers = 0) : Transport(
            _destination, _price, _distance) {
        passengers = _passengers;
    }

    double Price() const {
        if (passengers > 0) {
            return price - (200 * passengers);
        } else {
            return price;
        }
    }
};

void pecatiPoloshiPonudi(Transport **pTransport, int n, AvtomobilTransport transport) {
    const double priceThreshold = 1500;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pTransport[j]->getDistance() > pTransport[j + 1]->getDistance()) {
                Transport *temp = pTransport[j];
                pTransport[j] = pTransport[j + 1];
                pTransport[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (pTransport[i]->Price() > priceThreshold) {
            cout << pTransport[i]->getDestination();
            cout << " ";
            cout << pTransport[i]->getDistance();
            cout << " ";
            cout << pTransport[i]->Price() << endl;
        }
    }
}

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete[] ponudi;
    return 0;
}