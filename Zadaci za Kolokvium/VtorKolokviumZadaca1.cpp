#include<iostream>
#include<cstring>

using namespace std;

class Book {
protected:
    char isbn[21];
    char title[51];
    char author[31];
    double basePrice;
public:
    Book(const char *_isbn = "", const char *_title = "", const char *_author = "", double _basePrice = 0.0)
            : basePrice(_basePrice) {
        strcpy(isbn, _isbn);
        strcpy(title, _title);
        strcpy(author, _author);
    }

    void setISBN(char *isbn) {
        strcpy(this->isbn, isbn);
    }

    virtual ~Book() {

    }

    virtual double bookPrice() const = 0;

    bool operator<(const Book &rhs) const {
        if (isbn < rhs.isbn)
            return true;
        if (rhs.isbn < isbn)
            return false;
        if (title < rhs.title)
            return true;
        if (rhs.title < title)
            return false;
        if (author < rhs.author)
            return true;
        if (rhs.author < author)
            return false;
        return basePrice < rhs.basePrice;
    }

    bool operator>(const Book &other) const {
        return bookPrice() > other.bookPrice();
    }

    friend ostream &operator<<(ostream &os, Book &book) {
        os << book.isbn << ": " << book.title << ", " << book.author << " " << book.bookPrice() << endl;
        return os;
    }

};

class OnlineBook : public Book {
private:
    char *url;
    int sizeMB;
public:
    OnlineBook(const char *_isbn, const char *_title, const char *_author, double _basePrice, const char *_url,
               int _sizeMB)
            : Book(_isbn, _title, _author, _basePrice), sizeMB(_sizeMB) {
        int length = strlen(_url);
        url = new char[length + 1];
        strncpy(url, _url, length);
        url[length] = '\0';
    }

    OnlineBook(const OnlineBook &other)
            : Book(other.isbn, other.title, other.author, other.basePrice), sizeMB(other.sizeMB) {
        int length = strlen(other.url);
        url = new char[length + 1];
        strncpy(url, other.url, length);
        url[length] = '\0';
    }

    OnlineBook &operator=(const OnlineBook &other) {
        if (this != &other) {
            Book::operator=(other);
            delete[] url;
            int length = strlen(other.url);
            url = new char[length + 1];
            strncpy(url, other.url, length);
            url[length] = '\0';
            sizeMB = other.sizeMB;
        }
        return *this;
    }

    ~OnlineBook() {
        delete[]url;
    }

    double bookPrice() const {
        if (sizeMB > 20) {
            return basePrice * 0.2 + basePrice;
        }
        return basePrice;
    }

};

class PrintBook : public Book {
private:
    float weight;
    bool inStock;
public:
    PrintBook(const char *_isbn, const char *_title, const char *_author, double _basePrice, double _weight,
              bool _inStock) : Book(_isbn, _title, _author, _basePrice), weight(_weight), inStock(_inStock) {
    }

    PrintBook(const PrintBook &other) : Book(other.isbn, other.title, other.author, other.basePrice),
                                        weight(other.weight), inStock(other.inStock) {
    }

    double bookPrice() const {
        if (weight > 0.7) {
            return basePrice * 0.15 + basePrice;
        } else {
            return basePrice;
        }
    }

    PrintBook &operator=(const PrintBook &other) {
        if (this != &other) {
            Book::operator=(other);
            weight = other.weight;
            inStock = other.inStock;
        }
        return *this;
    }

};

void mostExpensiveBook(Book **books, int n) {
    int onlineCount = 0;
    int printCount = 0;

    cout << "FINKI-Education" << endl;

    for (int i = 0; i < n; i++) {
        OnlineBook *onlineBook = dynamic_cast<OnlineBook *>(books[i]);
        if (onlineBook)
            onlineCount++;
        else
            printCount++;
    }

    cout << "Total number of online books: " << onlineCount << endl;
    cout << "Total number of print books: " << printCount << endl;

    Book *mostExpensive = books[0];
    for (int i = 1; i < n; i++) {
        if (*books[i] > *mostExpensive)
            mostExpensive = books[i];
    }

    cout << "The most expensive book is:" << endl;
    cout << *mostExpensive;
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}