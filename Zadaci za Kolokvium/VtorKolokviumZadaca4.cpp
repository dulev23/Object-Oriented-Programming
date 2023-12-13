#include <cstring>
#include <iostream>

using namespace std;

// Your Code goes here
class Pizza {
protected:
    char name[20]{};
    char ingredients[100]{};
    float basePrice;
public:
    Pizza(char *_name = "", char *_ingredients = "", float _basePrice = 0.0) {
        strcpy(name, _name);
        strcpy(ingredients, _ingredients);
        basePrice = _basePrice;
    }

    virtual double price() const = 0;

    friend ostream &operator<<(ostream &os, const Pizza &pizza) {
        os << pizza.name << ": " << pizza.ingredients << " - " << pizza.price() << endl;
        return os;
    }

    bool operator<(const Pizza &rhs) const {
        return price() < rhs.price();
    }

};

enum Size {
    mala,
    golema,
    familijarna
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza(char *_name = "", char *_ingredients = "", float _basePrice = 0.0, enum Size _type = mala) : Pizza(_name,
                                                                                                                 _ingredients,
                                                                                                                 _basePrice),
                                                                                                           size(_type) {}

    double price() const {
        if (size == mala) {
            return basePrice + basePrice * 0.1;
        } else if (size == golema) {
            return basePrice + basePrice * 0.2;
        } else {
            return basePrice + basePrice * 0.3;
        }
    }

    friend ostream &operator<<(ostream &os, const FlatPizza &flatpizza) {
        os << flatpizza.name << ": " << flatpizza.ingredients << ", ";
        switch (flatpizza.size) {
            case mala:
                os << "small";
                break;
            case golema:
                os << "big";
                break;
            case familijarna:
                os << "family";
                break;
        }
        os << " - " << flatpizza.price() << endl;
        return os;
    }

};

class FoldedPizza : public Pizza {
private:
    bool white;
public:
    FoldedPizza(char *_name = "", char *_ingredients = "", float _basePrice = 0.0, bool _white = true) : Pizza(_name,
                                                                                                               _ingredients,
                                                                                                               _basePrice),
                                                                                                         white(_white) {
        white = _white;
    }

    double price() const {
        if (white) {
            return basePrice + basePrice * 0.1;
        } else {
            return basePrice + basePrice * 0.3;
        }
    }

    void setWhiteFlour(bool _white) {
        this->white = _white;
    }


    friend ostream &operator<<(ostream &os, const FoldedPizza &foldedpizza) {
        os << foldedpizza.name << ": " << foldedpizza.ingredients << ", ";
        if (foldedpizza.white) {
            os << "wf";
        } else {
            os << "nwf";
        }
        os << " - " << foldedpizza.price() << endl;
        return os;
    }
};

void expensivePizza(Pizza **pPizza, int n) {
    Pizza *max = pPizza[0];
    for (int i = 1; i < n; ++i) {
        if (pPizza[i]->price() > max->price()) {
            max = pPizza[i];
        }
    }
    if (FlatPizza *fPizza = dynamic_cast<FlatPizza *>(max)) {
        cout << *fPizza << endl;
    } else if (FoldedPizza *fPizza = dynamic_cast<FoldedPizza *>(max)) {
        cout << *fPizza << endl;
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}