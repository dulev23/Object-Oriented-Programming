#include<iostream>
#include<cstring>

using namespace std;

class NegativeValueException {
private:
    char productName[50];
public:
    NegativeValueException(char *name) {
        strcpy(this->productName, name);
    }

    void showMessage() {
        cout << "The product" << productName << "cannot have a negative value for the price" << endl;
    }
};

class Discount { //abstract class
public:
    static float EUR_TO_MKD;

    static float USD_TO_MKD;

    virtual float discount_price() = 0;

    virtual float getPrice() = 0;

    virtual void print_rule() = 0;
};

float Discount::EUR_TO_MKD = 61.5;
float Discount::USD_TO_MKD = 58.4;

class Product {
protected:
    char name[50];
    float price; //price is in EUR
public:
    Product(char *name = "", float price = 0.0) {
        strcpy(this->name, name);
        this->price = price;
    }

    void changePrice(float newPrice) {
        if (newPrice < 0) {
            throw NegativeValueException(this->name);
        }
        this->price = newPrice;
    }
};

class FoodProduct : public Product, public Discount {
public:
    FoodProduct(char *name = "", float price = 0.0) : Product(name, price) {

    }

    float discount_price() {
        return getPrice();
    }

    float getPrice() {
        return price * Discount::EUR_TO_MKD;
    }

    void print_rule() {
        cout << "No discount for food products" << endl;
    }
};

class Drinks : public Product, public Discount {
private:
    bool isAlcohol;
public:
    Drinks(char *name = "", float price = 0.0, bool isAlcohol = false) : Product(name, price) {
        this->isAlcohol = isAlcohol;
    }

    float discount_price() {
        if (isAlcohol && price > 20.0) {
            return getPrice() * 0.95;
        }
        if (!isAlcohol && strcmp(name, "coca-cola") == 0) {
            return getPrice() * 0.9;
        }
        return getPrice();
    }

    float getPrice() {
        return price * Discount::EUR_TO_MKD;
    }

    void print_rule() {
        cout << "Alcohol product with price larger than 20EUR ->5%; Coca cola 10%" << endl;
    }
};

class Cosmetics : public Product, public Discount {
public:
    Cosmetics(char *name = "", float price = 0.0, bool isAlcohol = false) : Product(name, price) {

    }

    float discount_price() {
        float priceInUSD = price * Discount::EUR_TO_MKD / Discount::USD_TO_MKD;
        if (priceInUSD > 20.0) {
            return getPrice() * 0.86;
        }
        if (price > 5.0) {
            return getPrice() * 0.88;
        }
        return getPrice();
    }

    float getPrice() {
        return price * Discount::EUR_TO_MKD;
    }

    void print_rule() {
        cout << "price in USD > 20$ -> 14%; price in EUR > 5EUR -> 12%" << endl;
    }

};

int main() {
//    Product *p = new FoodProduct("leb",0.5);
//    try{
//        p->changePrice(10);
//    } catch(NegativeValueException e){
//        e.showMessage();
//    }
    int n = 0;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("leb", 0.5);
    d[n++] = new Drinks("viski", 20, true);
    d[n++] = new FoodProduct("sirenje", 6.2);
    d[n++] = new Drinks("vodka", 10, true);
    d[n++] = new Cosmetics("krema", 12);
    d[n++] = new Drinks("coca-cola", 1.2, false);
    d[n++] = new Cosmetics("parfem", 50);

    for (int i = 0; i < n; ++i) {
        cout << i + 1 << endl;
        cout << d[i]->getPrice() << endl;
        cout << d[i]->discount_price() << endl;
        d[i]->print_rule();
    }

    for (int i = 0; i < n; ++i) {
        Cosmetics *cosmetics = dynamic_cast<Cosmetics *>(d[i]);
        if (cosmetics != 0) {
            int newPrice;
            cin >> newPrice;
            try {
                cosmetics->changePrice(newPrice);
            }
            catch (NegativeValueException e) {
                e.showMessage();
            }
        }
    }

    return 0;
}