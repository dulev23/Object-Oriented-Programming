#include<iostream>
#include<cstring>

using namespace std;

class FoodItem {
protected:
    char *type;
    int num;
public:
    FoodItem() {
        type = new char[20];
        strcpy(this->type, "empty");
        num = 0;
    }

    FoodItem(char *t, int n) {
        type = new char[strlen(t) + 1];
        strcpy(type, t);
        num = n;
    }

    FoodItem(const FoodItem &fi) {
        type = new char[strlen(fi.type) + 1];
        num = fi.num;
    }

    FoodItem &operator=(const FoodItem &fi) {
        if (this != &fi) {
            delete[]type;
            type = new char[strlen(fi.type) + 1];
            num = fi.num;
        }
        return *this;
    }

    char *getType() const {
        return type;
    }

    virtual int getPrice() = 0;

    virtual int getTime() = 0;

    virtual ~FoodItem() {
        delete[]type;
    }

};

class Pizza : public FoodItem {
private:
    char *dough;
public:
    Pizza(char *type, int num, char *d) : FoodItem(type, num) {
        dough = new char[strlen(d) + 1];
        strcpy(dough, d);
    }

    Pizza(const Pizza &p) {
        dough = new char[strlen(p.dough) + 1];
        strcpy(dough, p.dough);
    }

    ~Pizza() {
        delete[]dough;
    }

    int getTime() {
        return 25;
    }

    int getPrice() {
        if (strcmp(dough, "wholeWheat") == 0) {
            return 250 * num;
        } else if (strcmp(dough, "glutenFree") == 0) {
            return 350 * num;
        } else {
            return 0;
        }
    }
};

class Steak : public FoodItem {
private:
    bool cooked;
public:
    Steak(char *type, int num, bool cooked = false) : FoodItem(type, num) {
        this->cooked = cooked;
    }

    int getPrice() {
        return 1300 * num;
    }

    int getTime() {
        if (cooked) {
            return 20;
        } else if (!cooked) {
            return 15;
        } else {
            return 0;
        }
    }

    ~Steak() {}
};

FoodItem *getMaxFoodItem(FoodItem *pItem[], int n) {
    FoodItem *max = pItem[0];
    for (int i = 0; i < n; ++i) {
        if (pItem[i]->getPrice() > max->getPrice()) {
            max = pItem[i];
        }
    }
    return max;
}

int main() {
    FoodItem *p;
    int n;
    cin >> n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i < n; ++i) {
        cin >> type;
        cin >> size;

        if (strcmp(type, "pizza") == 0) {
            cin >> dough;
            items[i] = new Pizza(type, size, dough);
        } else {
            cin >> cooked;
            items[i] = new Steak(type, size, cooked);
        }
    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout << "Type: " << it->getType() << endl;
    cout << "The max price is: " << it->getPrice() << endl;
    cout << "Time to cook: " << it->getTime();
    return 0;
}