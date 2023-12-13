#include<iostream>
#include<cstring>

using namespace std;

enum Extension {
    pdf, txt, exe
};

class File {
private:
    char *ime;
    Extension extension;
    char *ime_sopstvenik;
    int golemina;

    const char *getExtensionName(Extension ext) {
        switch (ext) {
            case pdf:
                return "pdf";
            case txt:
                return "txt";
            case exe:
                return "exe";
        }
    }

public:
    File(char *i = "", char *i_S = "", int Golemina = 0, Extension ext = txt) {
        this->ime = new char[strlen(i) + 1];
        strcpy(this->ime, i);
        this->extension = ext;
        this->ime_sopstvenik = new char[strlen(i_S) + 1];
        strcpy(this->ime_sopstvenik, i_S);
        this->golemina = Golemina;
    }

    File(const File &f) {
        this->ime = new char[strlen(f.ime) + 1];
        strcpy(this->ime, f.ime);
        this->extension = f.extension;
        this->ime_sopstvenik = new char[strlen(f.ime_sopstvenik) + 1];
        strcpy(this->ime_sopstvenik, f.ime_sopstvenik);
        this->golemina = f.golemina;
    }

    ~File() {
        delete[]ime;
        delete[]ime_sopstvenik;
    }

    File &operator=(const File &f) {
        if (this != &f) {
            delete[]ime;
            delete[]ime_sopstvenik;
            this->ime = new char[strlen(f.ime) + 1];
            strcpy(this->ime, f.ime);
            this->extension = f.extension;
            this->ime_sopstvenik = new char[strlen(f.ime_sopstvenik) + 1];
            strcpy(this->ime_sopstvenik, f.ime_sopstvenik);
            this->golemina = f.golemina;
        }
        return *this;
    }

    void print() {
        cout << "File name: " << ime << "." << getExtensionName(extension) << endl;
        cout << "File owner: " << ime_sopstvenik << endl;
        cout << "File size: " << golemina << endl;
    }

    bool equals(const File &that) {
        return (strcmp(this->ime, that.ime) == 0 && strcmp(this->ime_sopstvenik, that.ime_sopstvenik) == 0 &&
                this->extension == that.extension);
    }

    bool equalsType(const File &that) {
        return (strcmp(this->ime, that.ime) == 0 && this->extension == that.extension);
    }
};

class Folder {
private:
    char *ime;
    int datoteki;
    File *files;
public:
    Folder(const char *i) {
        ime = new char[strlen(i) + 1];
        strcpy(ime, i);
        datoteki = 0;
        files = nullptr;
    }

    Folder(const Folder &f) {
        this->ime = new char[strlen(f.ime) + 1];
        strcpy(this->ime, f.ime);
        datoteki = f.datoteki;
        files = new File[f.datoteki];
        for (int i = 0; i < f.datoteki; ++i) {
            files[i] = f.files[i];
        }
    }

    Folder &operator=(const Folder &f) {
        if (this != &f) {
            delete[]ime;
            delete[]files;
            this->ime = new char[strlen(f.ime) + 1];
            strcpy(this->ime, f.ime);
            datoteki = f.datoteki;
            files = new File[f.datoteki];
            for (int i = 0; i < f.datoteki; ++i) {
                files[i] = f.files[i];
            }
        }
        return *this;
    }

    ~Folder() {
        delete[]ime;
        delete[]files;
    }

    void remove(const File &file) {
        for (int i = 0; i < datoteki; i++) {
            if (files[i].equals(file)) {
                for (int j = i; j < datoteki - 1; j++) {
                    files[j] = files[j + 1];
                }
                datoteki--;
                break;
            }
        }
    }

    void add(const File &file) {
        File *file1 = new File[datoteki + 1];
        for (int i = 0; i < datoteki; ++i) {
            file1[i] = files[i];
        }
        file1[datoteki++] = file;
        delete[]files;
        files = file1;
    }

    void print() {
        cout << "Folder name: " << ime << endl;
        for (int i = 0; i < datoteki; ++i) {
            files[i].print();
        }
    }

};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}