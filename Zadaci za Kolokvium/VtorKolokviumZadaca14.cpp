#include<iostream>
#include<cstring>

using namespace std;

class SMS {
protected:
    char pretplatnik[13];
    float basePrice;
public:
    SMS(char *_pretplatnik = "", float _basePrice = 0.0) {
        strcpy(pretplatnik, _pretplatnik);
        basePrice = _basePrice;
    }

    virtual double SMS_cena() const {
        return basePrice * 1.18;
    };

    friend ostream &operator<<(ostream &os, const SMS &sms) {
        os << "Tel: " << sms.pretplatnik << " - cena: " << sms.SMS_cena() << "den." << endl;
        return os;
    }

};

class RegularSMS : public SMS {
private:
    char *textMessage;
    bool roaming;
    static float rPercentage;
public:
    RegularSMS(char *_pretplatnik = "", float _basePrice = 0, char *_textMessage = "", bool _roaming = false) : SMS(
            _pretplatnik, _basePrice) {
        textMessage = new char[strlen(_textMessage) + 1];
        strcpy(textMessage, _textMessage);
        roaming = _roaming;
    }

    RegularSMS(const RegularSMS &regularSms) {
        textMessage = new char[strlen(regularSms.textMessage) + 1];
        strcpy(textMessage, regularSms.textMessage);
        roaming = regularSms.roaming;
    }

    RegularSMS &operator=(const RegularSMS &regularSms) {
        if (this != &regularSms) {
            delete[]textMessage;
            textMessage = new char[strlen(regularSms.textMessage) + 1];
            strcpy(textMessage, regularSms.textMessage);
            roaming = regularSms.roaming;
        }
    }

    ~RegularSMS() {
        delete[]textMessage;
    }

    double SMS_cena() const {
        float numMessages =
                (strlen(textMessage) + 159) / 160;  // Calculate the number of messages needed to accommodate the text
        float cena = basePrice * numMessages;

        if (roaming)
            return cena * (rPercentage + 1.0);
        else
            return cena * 1.18;  // Increase the base price by 18% for domestic messages
    }

    static void set_rProcent(float rPercentage) {
        RegularSMS::rPercentage = rPercentage / 100;
    }

};

float RegularSMS::rPercentage = 3.0;

class SpecialSMS : public SMS {
private:
    bool humanitarni;
    static float sPercentage;
public:
    SpecialSMS(char *_pretplatnik = "", float _basePrice = 0, bool _humanitarni = false) : SMS(_pretplatnik,
                                                                                               _basePrice) {
        humanitarni = _humanitarni;
    }

    double SMS_cena() const {
        if (!humanitarni) {
            return basePrice * sPercentage + basePrice;
        } else {
            return basePrice;
        }
    }

    static void set_sProcent(float sPercentage) {
        SpecialSMS::sPercentage = sPercentage / 100;
    }


//    friend ostream &operator<<(ostream &os, const SpecialSMS &sms) {
//        os << "Tel: " << sms.pretplatnik << " - cena: " << sms.SMS_cena()<<"den."<<endl;
//        return os;
//    }
};

float SpecialSMS::sPercentage = 1.5;

void vkupno_SMS(SMS **poraka, int n) {
    int regularCount = 0, specialCount = 0;
    float regularTotalPrice = 0.0, specialTotalPrice = 0.0;

    for (int i = 0; i < n; i++) {
        if (dynamic_cast<RegularSMS *>(poraka[i]) != nullptr) {
            regularCount++;
            regularTotalPrice += poraka[i]->SMS_cena();
        } else if (dynamic_cast<SpecialSMS *>(poraka[i]) != nullptr) {
            specialCount++;
            specialTotalPrice += poraka[i]->SMS_cena();
        }
    }

    cout << "Vkupno ima " << regularCount << " regularni SMS poraki i nivnata cena e: " << regularTotalPrice << endl;
    cout << "Vkupno ima " << specialCount << " specijalni SMS poraki i nivnata cena e: " << specialTotalPrice << endl;

}

int main() {

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}