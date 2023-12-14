#include<iostream>
#include<cstring>

using namespace std;

class Film {
private:
    char name[100];
    double rating;
    double revenue;
public:
    Film() {//default constructor
    }

    Film(char *n, double rate, double rev) { //constructor with parameters
        strcpy(name, n);
        rating = rate;
        revenue = rev;
    }

    ~Film() {//destructor
    }

    char *getName() {
        return name;
    }

    double getRating() {
        return rating;
    }

    double getRevenue() {
        return revenue;
    }

    void setName(char n[50]) {
        strcpy(name, n);
    }

    void setRating(double r) {
        rating = r;
    }

    void setRevenue(double rev) {
        revenue = rev;
    }

    void display() {
        setName(name);
        setRevenue(revenue);
        setRating(rating);
        cout << "Name of film: " << getName() << endl;
        cout << "Rating: " << getRating() << endl;
        cout << "Revenue: " << getRevenue() << endl;
    }
};

void printMostPopularFilm(Film *films, int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (films[i].getRevenue() > films[maxIndex].getRevenue()) {
            maxIndex = i;
        }
    }
    cout << "Name of film: " << films[maxIndex].getName() << endl;
    cout << "Rating: " << films[maxIndex].getRating() << endl;
    cout << "Revenue: " << films[maxIndex].getRevenue() << endl;
}

int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin >> name;
    cin >> rating;
    cin >> revenue;
    films[n - 1].setName(name);
    films[n - 1].setRating(rating);
    films[n - 1].setRevenue(revenue);

    cout << "-->Testing set methods and display()" << endl;
    films[n - 1].display();
    cout << endl;

    cout << "-->Testing printMostPopularFilm()" << endl;
    printMostPopularFilm(films, n);
    return 0;
}