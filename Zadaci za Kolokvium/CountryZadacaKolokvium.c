#include<stdio.h>

typedef struct President {
    char name[100];
    char surname[100];
    char party[100];
} President;

typedef struct City {
    char name[100];
    int population;
} City;

typedef struct Country {
    char name[100];
    President president;
    City capital;
    int population;
} Country;

void readPresident(President *p) {
    scanf("%s %s %s", p->name, p->surname, p->party);
}

void printPresident(President p) {
    printf("President Name: %s, President Surname: %s, President Party: %s\n", p.name, p.surname, p.party);
}

void readCity(City *c) {
    scanf("%s %d", c->name, &c->population);
}

void printCity(City c) {
    printf("City name: %s, City population: %d\n", c.name, c.population);
}

void readCountry(Country *c) {
    scanf("%s", c->name);
    readPresident(&c->president);
    readCity(&c->capital);
    scanf("%d", &c->population);
}

void printCountry(Country c) {
    printf("Country name: %s ", c.name);
    printPresident(c.president);
    printCity(c.capital);
    printf("Country population: %d ", c.population);
}

int compare(Country c1, Country c2) {
    if (c1.capital.population > c2.capital.population) {
        return 1;
    } else if (c1.capital.population < c2.capital.population) {
        return -1;
    } else {
        return 0;
    }
}

void printCountryWithLargestCapital(Country *countries, int n) {
    Country maxCountry = countries[0];
    for (int i = 1; i < n; ++i) {
        if (compare(countries[i], maxCountry) > 0) {
            maxCountry = countries[i];
        }
    }
    printCountry(maxCountry);
}

int main() {
    Country countries[100];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        readCountry(&countries[i]);
    }

    printCountryWithLargestCapital(countries, n);
    return 0;
}