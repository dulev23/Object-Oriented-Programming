#include<iostream>
#include<cstring>

#define MAX 50

using namespace std;

enum typeC {
    standard,
    loyal,
    vip
};

class Customer {
protected:
    char name[50]{};
    char email[50]{};
    typeC type;
    static int basePopust;
    static int bonusPopust;
    int boughtItems;
public:
    Customer(const char *_name = "Petko", const char *_email = "finki@ukim.mk", typeC _type = standard,
             int _boughtItems = 0) {
        strcpy(name, _name);
        strcpy(email, _email);
        type = _type;
        boughtItems = _boughtItems;
    }

    static void setDiscount1(int discount) {
        basePopust = discount;
    }

    int popust() const {
        if (type == 0) {
            return 0;
        } else if (type == 1) {
            return basePopust;
        } else {
            return basePopust + bonusPopust;
        }
    }

    const char *getName() const {
        return name;
    }

    const char *getEmail() const {
        return email;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer) {
        os << customer.name << endl;
        os << customer.email << endl;
        os << customer.boughtItems << endl;
        switch (customer.type) {
            case standard:
                os << "standard";
                break;
            case loyal:
                os << "loyal";
                break;
            case vip:
                os << "vip";
                break;
        }
        os << " " << customer.popust() << endl;
        return os;
    }

    typeC getType() const {
        return type;
    }

    virtual void setType(typeC type) {
        Customer::type = type;
    }

    int getBoughtItems() const {
        return boughtItems;
    }

};

int Customer::basePopust = 10;
int Customer::bonusPopust = 20;

class UserExistsException {
private:
    char userExists[50];
public:
    UserExistsException(const char *_userExists = "") {
        strcpy(userExists, _userExists);
    }

    void showMessage() {
        cout << "The user already exists in the list!" << endl;
    }

};

class FINKI_bookstore {
private:
    Customer **customers;
    int numCustomers;
public:
    FINKI_bookstore() {}

    FINKI_bookstore(const FINKI_bookstore &fb) {
        numCustomers = fb.numCustomers;
        customers = new Customer *[numCustomers];
        for (int i = 0; i < numCustomers; ++i) {
            customers[i] = fb.customers[i];
        }
    }

    void setCustomers(Customer *customer, int n) {
        customers = new Customer *[n];
        for (int i = 0; i < n; ++i) {
            customers[i] = &customer[i];
        }
        numCustomers = n;
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &fb) {
        if (this != &fb) {
            delete[]customers;
            numCustomers = fb.numCustomers;
            customers = new Customer *[numCustomers];
            for (int i = 0; i < numCustomers; ++i) {
                customers[i] = fb.customers[i];
            }
        }
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &bookstore) {
        for (int i = 0; i < bookstore.numCustomers; ++i) {
            os << *(bookstore.customers[i]);
        }
        return os;
    }

    virtual void update() {
        for (int i = 0; i < numCustomers; ++i) {
            Customer *currentCustomer = customers[i];
            if (currentCustomer->getType() == 0 && currentCustomer->getBoughtItems() > 5) {
                currentCustomer->setType(loyal);
            } else if (currentCustomer->getType() == 1 && currentCustomer->getBoughtItems() > 10) {
                currentCustomer->setType(vip);
            }
        }
    }

    FINKI_bookstore &operator+=(const Customer &nC) {
        for (int i = 0; i < numCustomers; ++i) {
            if (strcmp(customers[i]->getEmail(), nC.getEmail()) == 0) {
                throw UserExistsException("The user already exists in the list!");
            }
        }
        Customer **newCustomers = new Customer *[numCustomers + 1];

        for (int i = 0; i < numCustomers; ++i) {
            newCustomers[i] = customers[i];
        }

        newCustomers[numCustomers] = new Customer(nC);

        delete[] customers;
        customers = newCustomers;
        ++numCustomers;
        return *this;
    }

    ~FINKI_bookstore() {
        delete[]customers;
    }

};


int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
            cout << fc;
        }
        catch (UserExistsException ue) {
            ue.showMessage();
        }
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
            cout << fc;
        }
        catch (UserExistsException &ue) {
            ue.showMessage();
            cout << fc;
        }

    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}