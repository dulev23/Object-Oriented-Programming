#include<iostream>
#include<cstring>

using namespace std;

class DisciplinaryAction {
private:
    char *Name;
    int Index;
    char *Reason;
public:
    DisciplinaryAction(char *name = "", int index = 0, char *reason = "") {
        this->Name = new char[strlen(name) + 1];
        strcpy(this->Name, name);
        this->Index = index;
        this->Reason = new char[strlen(reason) + 1];
        strcpy(this->Reason, reason);
    }

    DisciplinaryAction(const DisciplinaryAction &DA) {
        this->Name = new char[strlen(DA.Name) + 1];
        strcpy(this->Name, DA.Name);
        this->Index = DA.Index;
        this->Reason = new char[strlen(DA.Reason) + 1];
        strcpy(this->Reason, DA.Reason);
    }

    ~DisciplinaryAction() {
        delete[] Name;
        delete[] Reason;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &DA) {
        if (this != &DA) {
            delete[] Name;
            delete[] Reason;
            this->Name = new char[strlen(DA.Name) + 1];
            strcpy(this->Name, DA.Name);
            this->Index = DA.Index;
            this->Reason = new char[strlen(DA.Reason) + 1];
            strcpy(this->Reason, DA.Reason);
        }
        return *this;
    }

    void setIndex(int ind) {
        Index = ind;
    }

    int get_index() {
        return Index;
    }

    void print() {
        cout << "Student: " << Name << endl;
        cout << "Student's index: " << Index << endl;
        cout << "Reason: " << Reason << endl;
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

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}