#include<iostream>
#include<cstring>
using namespace std;

class Product{
protected:
    char name[50];
    float price;
public:
    Product(char *name="", float price=0.0){
        strcpy(this->name,name);
        this->price=price;
    }
};

class Discountable{ //interface
public:
    virtual float getPrice()=0;

    virtual float getPriceWithDiscount()=0;

    virtual void print()=0;
};

class FoodProduct : public Product, public Discountable {
private:
    int calories;
public:
    FoodProduct(char *name="", float price=0.0, int calories=0) : Product(name,price){
        this->calories=calories;
    }

    float getPrice(){
        return price;
    }

    float getPriceWithDiscount(){
        if(calories>500){
            return 0.8*price;
        }
        else if(calories>100) {
            return 0.9 * price;
        }
        else{
            return 0.95*price;
        }
    }

    void print(){
        cout<<"FoodProduct "<< name<<" with # of calories: "<<calories<<" Price: "<<getPrice()<<" Price with discount: "<<getPriceWithDiscount()<<endl;

    }
};

class DigitalProduct : public Product, public Discountable{
private:
    float sizeInMB;
public:
    DigitalProduct(char *name="", float price=0.0, float sizeInMB=0.0) : Product(name,price){
        this->sizeInMB=sizeInMB;
    }

    float getPrice(){
        return price;
    }

    float getPriceWithDiscount(){
        if(sizeInMB>1024){
            return 0.7*price;
        }
        else if(sizeInMB>512){
            return 0.85*price;
        }
        else{
            return 0.925*price;
        }
    }

    void print(){
        cout<<"DigitalProduct "<<name<<" with size in MBs: "<<sizeInMB<<" Price: "<<getPrice()
        <<" Price with discount: "<<getPriceWithDiscount()<<endl;
    }
};

float totalDiscount(Discountable **pDiscountable, int n){
    float totalDiscount=0.0;
    for (int i = 0; i < n; ++i) {
        totalDiscount+=(pDiscountable[i]->getPrice()-pDiscountable[i]->getPriceWithDiscount());
    }
    return totalDiscount;
}

int countFoodProducts(Discountable **pDiscountable, int n) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        FoodProduct *casted = dynamic_cast<FoodProduct *>(pDiscountable[i]);
        if (casted != 0) {
            counter++;
        }
    }
    return counter;
}

int main(){
    int n;
    cin>>n;

    Discountable **pDiscountable=new Discountable * [n];
    for (int i = 0; i < n; ++i) {
        int type; //1 = food 2 = digital
        char name[50];
        float price;
        float sizeInMB;
        int calories;
        cin>>type;
        if(type==1){ //FoodProduct
            cin>>name>>price>>calories;
            pDiscountable[i]=new FoodProduct(name,price,calories);
        }
        else{ //DigitalProduct
            cin>>name>>price>>sizeInMB;
            pDiscountable[i]=new DigitalProduct(name,price,sizeInMB);
        }
    }

    for (int i = 0; i < n; ++i) {
        pDiscountable[i]->print();
    }

    cout<<"Total discount for the products is: "<<totalDiscount(pDiscountable,n);

    cout<<"Total number of food products" <<countFoodProducts(pDiscountable, n);

    cout<<"Total number of digital products"<<n - countFoodProducts(pDiscountable,n);

    return 0;
}