#include<iostream>
#include<cstring>

using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country() {
    }

    Country(char *n, char *c, double a, double p) {
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }

    ~Country() {
    }

    void setName(char n[100]) {
        strcpy(name, n);
    }

    void setCapital(char c[100]) {
        strcpy(capital, c);
    }

    void setArea(double a) {
        area = a;
    }

    void setPopulation(double p) {
        population = p;
    }

    char *getName() {
        return name;
    }

    char *getCapital() {
        return capital;
    }

    double getArea() {
        return area;
    }

    double getPopulation() {
        return population;
    }

    void display() {
        cout << "Country: " << getName() << endl;
        cout << "Capital: " << getCapital() << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Population: " << getPopulation() << endl;
    }
};


void sortCountries(Country *countries, int n) {
    Country c;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (countries[j].getArea() < countries[i].getArea()) {
                c = countries[i];
                countries[i] = countries[j];
                countries[j] = c;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        countries[i].display();
    }
}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> capital;
        cin >> area;
        cin >> population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }

    // testing set methods and display for last element
    cin >> name;
    cin >> capital;
    cin >> area;
    cin >> population;
    countries[n - 1].setName(name);
    countries[n - 1].setCapital(capital);
    countries[n - 1].setArea(area);
    countries[n - 1].setPopulation(population);

    cout << "-->Testing set methods and display()" << endl;
    countries[n - 1].display();
    cout << endl;

    cout << "-->Testing sortCountries()" << endl;
    sortCountries(countries, n);
    return 0;
}