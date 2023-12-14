#include<iostream>
#include<cstring>

using namespace std;

class BasketballPlayer {
private:
    char ime[20];
    char prezime[20];
    int dresBr;
    int poeni_1;
    int poeni_2;
    int poeni_3;
public:
    BasketballPlayer(char *i, char *p, int dres, int p1, int p2, int p3) {
        strcpy(ime, i);
        strcpy(prezime, p);
        dresBr = dres;
        poeni_1 = p1;
        poeni_2 = p2;
        poeni_3 = p3;
    }

    float avg_pts() {
        return float(poeni_1 + poeni_2 + poeni_3) / 3;
    }

    void print() {
        cout << "Player: " << ime << " " << prezime << " with number: " << dresBr << " has " << avg_pts()
             << " points on average" << endl;
    }
};

int main() {
    char ime[20];
    char prezime[20];
    int dresBR;
    int poeni1, poeni2, poeni3;
    cin >> ime >> prezime >> dresBR >> poeni1 >> poeni2 >> poeni3;
    BasketballPlayer BP(ime, prezime, dresBR, poeni1, poeni2, poeni3);
    BP.print();
    return 0;
}