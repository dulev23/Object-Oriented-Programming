#include<iostream>
#include<cstring>

using namespace std;

class HotelReservation {
protected:
    int days;
    int guests;
    char contact[50];
public:
    HotelReservation(char *contact, int days, int guests) {
        strcpy(this->contact, contact);
        this->guests = guests;
        this->days = days;
    }

    virtual double price() {
        return guests * days * 25;
    }

    double price(double deposit) {
        return deposit - price();
    }
};

class HalfBoardHotelReservation : public HotelReservation {
public:
    HalfBoardHotelReservation(char *contact, int days, int guests) : HotelReservation(contact, days, guests) {

    }

    double price() {
        return HotelReservation::price() * 1.2;
    }
};

class Hotel {
    char name[20];
    double balance;
public:
    Hotel(char *name = "Eftalia", double balance = 0) {
        strcpy(this->name, name);
        this->balance = balance;
    }

    double depositReservation(HotelReservation &hr, double deposit) {
        double totalPrice = hr.price();
        balance += totalPrice;
        return hr.price(deposit);
    }

    friend ostream &operator<<(ostream &out, const Hotel &h) {
        return out << h.name << " " << h.balance;
    }
};

int main() {
    Hotel hotel("Finki hotel", 0);

    int n;
    cin >> n;
    HotelReservation **reservations = new HotelReservation *[n];

    for (int i = 0; i < n; ++i) {
        int type; //1=obicna 2=halfboard
        char name[30];
        int days, guests;
        double deposit;
        cin >> type >> name >> days >> guests >> deposit;
        if (type == 1) {
            reservations[i] = new HotelReservation(name, days, guests);
        } else {
            reservations[i] = new HalfBoardHotelReservation(name, days, guests);
        }
        cout << name << " Days: " << days << " Guests: " << guests << " Reservations: " << reservations[i]->price()
             << endl;
        cout << " Change from payment: " << hotel.depositReservation(*reservations[i], deposit) << endl;
    }
    cout << "Hotel state after all the reservations were paid" << endl;
    cout << hotel;
    return 0;
}
