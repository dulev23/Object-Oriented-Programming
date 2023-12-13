#include<iostream>
#include<cstring>

using namespace std;

class DisciplinaryAction {
private:
    char *name;
    int index;
    char *reason;
    int n;
public:
    DisciplinaryAction(char *name = "", int index = 0, char *reason = "", int n = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->index = index;
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
        this->n = n;
    }

//    DisciplinaryAction() {
//        name="";
//        index=0;
//        reason="";
//        n=0;
//    }
//
//    DisciplinaryAction(char *ime,int ind,char *r,int broj){
//        name=new char[strlen(ime)+1];
//        strcpy(name,ime);
//        index=ind;
//        reason=new char[strlen(r)+1];
//        strcpy(reason,r);
//        n=broj;
//    }

    DisciplinaryAction(const DisciplinaryAction &da) {
        name = new char[strlen(da.name) + 1];
        strcpy(name, da.name);
        index = da.index;
        reason = new char[strlen(da.reason) + 1];
        strcpy(reason, da.reason);
        n = da.n;
    }


    void setIndex(int ind) {
        index = ind;
    }

    int getIndex() const {
        return index;
    }

    ~DisciplinaryAction() {
        delete[]name;
        delete[]reason;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &da) {
        if (this != &da) {
            delete[]name;
            delete[]reason;
            name = new char[strlen(da.name) + 1];
            strcpy(name, da.name);
            index = da.index;
            reason = new char[strlen(da.reason) + 1];
            strcpy(reason, da.reason);
            n = da.n;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const DisciplinaryAction &action) {
        os << "Student: " << action.name << endl;
        os << "Student's index: " << action.index << endl;
        os << "Reason: " << action.reason << endl;
        os << "Sessions: " << action.n << endl;
        return os;
    }

    bool operator<(const DisciplinaryAction &da) const {
        return n < da.n;
    }

    bool operator>(const DisciplinaryAction &da) const {
        return da < *this;
    }

    bool operator<=(const DisciplinaryAction &da) const {
        return !(da < *this);
    }

    bool operator>=(const DisciplinaryAction &da) const {
        return !(*this < da);
    }

    DisciplinaryAction &operator++() {
        n++;
        return *this;
    }
};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}