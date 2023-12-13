#include<iostream>
#include<cstring>

using namespace std;

class Book {
private:
    char *name;
    int *ISBN;
    int numOfPages;
public:
    Book(const char *n = "", const int *isbn = nullptr, int nOP = 0) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        ISBN = new int[5];
        for (int i = 0; i < 5; ++i) {
            ISBN[i] = isbn ? ISBN[i] : 0;
        }
        numOfPages = nOP;
    }

    Book(const Book &b) {
        name = new char[strlen(b.name) + 1];
        strcpy(name, b.name);
        numOfPages = b.numOfPages;
        ISBN = new int[b.numOfPages];
        for (int i = 0; i < b.numOfPages; ++i) {
            ISBN[i] = b.ISBN[i];
        }
    }

    Book &operator=(const Book &b) {
        if (this != &b) {
            delete[]name;
            name = new char[strlen(b.name) + 1];
            strcpy(name, b.name);
            numOfPages = b.numOfPages;
            delete[]ISBN;
            ISBN = new int[b.numOfPages];
            for (int i = 0; i < b.numOfPages; ++i) {
                ISBN[i] = b.ISBN[i];
            }
        }
        return *this;
    }

    ~Book() {
        delete[]name;
        delete[]ISBN;
    }

    bool operator==(const Book &b) const {
        return ISBN == b.ISBN;
    }

    int getNumOfPages() const {
        return numOfPages;
    }
};

class BorrowABook {
private:
    char name[100];
    Book *niza;
    int brKnigi;
public:
    BorrowABook(char *n) {
        brKnigi = 0;
        niza = new Book[0];
        strcpy(name, n);
    }

    BorrowABook(const BorrowABook &bab) {
        strcpy(name, bab.name);
        brKnigi = bab.brKnigi;
        niza = new Book[brKnigi];
        for (int i = 0; i < brKnigi; ++i) {
            niza[i] = bab.niza[i];
        }
    }

    BorrowABook &operator=(const BorrowABook &bab) {
        if (this != &bab) {
            strcpy(name, bab.name);
            delete[]niza;
            niza = new Book[brKnigi];
            brKnigi = bab.brKnigi;
            for (int i = 0; i < brKnigi; ++i) {
                niza[i] = bab.niza[i];
            }
        }
        return *this;
    }

    ~BorrowABook() {
        delete[]niza;
    }

    BorrowABook &operator+=(const Book &b) {
        Book *tmp = new Book[brKnigi + 1];
        for (int i = 0; i < brKnigi; ++i) {
            tmp[i] = niza[i];
        }
        tmp[brKnigi++] = b;
        delete[]niza;
        niza = tmp;
        return *this;
    }

    BorrowABook &operator-=(const Book &bab) {
        int flag = 0;
        for (int i = 0; i < brKnigi; ++i) {
            if (bab == niza[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            return *this;
        }
        Book *tmp = new Book[brKnigi - 1];
        int j = 0;
        for (int i = 0; i < brKnigi; ++i) {
            tmp[j] = niza[i];
            j++;
        }
        brKnigi--;
        delete[]niza;
        niza = tmp;
        return *this;
    }

    void printNumberOfPages(int max) const {
        cout << name << endl;
        for (int i = 0; i < brKnigi; i++) {
            if (niza[i].getNumOfPages() > max) {
                cout << niza[i];
            }
        }
    }
};

int main() {
    BorrowABook library("FINKI-Library");
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char title[100];
        int isbn[5];
        int pages;

        cin >> title;

        for (int i = 0; i < 5; i++)
            cin >> isbn[i];

        cin >> pages;

        Book nov = Book(title, isbn, pages);

        //adding a new book
        library += nov;
    }

    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin >> title;
    for (int i = 0; i < 5; i++)
        cin >> isbn[i];
    cin >> pages;

    Book greshka = Book(title, isbn, pages);

    //deleting a book
    library -= greshka;

    library.printNumberOfPages(150);

    return 0;
}