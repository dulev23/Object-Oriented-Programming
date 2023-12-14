#include<iostream>
#include<cstring>

using namespace std;

class EmailMessage {
private:
    char sender[50];
    char receiver[50];
    char subject[50];
    char body[300];
public:
    EmailMessage(char *_sender, char *_receiver, char *_subject, char *_body) {
        strcpy(sender, _sender);
        strcpy(receiver, _receiver);
        strcpy(subject, _subject);
        strcpy(body, _body);
    }

    void show() {
        cout << "From   :\t" << sender << endl;
        cout << "To     :\t" << receiver << endl;
        cout << "--------------------------------" << endl;
        cout << "Subject:\t" << subject << endl;
        cout << "--------------------------------" << endl;
        cout << "Body: " << endl;
        cout << body << endl;
        cout << "END";
    }
};

bool valid(char emailAddress[50]);

int main() {
    char sender[50];
    char receiver[50];
    char subject[50];
    char body[300];

    cin >> sender >> receiver;
    if (!valid(sender) || !valid(receiver)) {
        cout << "Sender or receiver has an invalid address!";
        return 0;
    }

    cin >> subject;
    cin.getline(subject, 50);
    cin.getline(body, 300);
    EmailMessage emailMessage(sender, receiver, subject, body);
    emailMessage.show();
    return 0;
}

bool valid(char mailAddress[50]) {
    int indx = -1;
    for (int i = 0; i < strlen(mailAddress); ++i) {
        if (mailAddress[i] == '@')
            indx = i;
    }
    if (indx == -1) { //Ne sme nasle @
        return false;
    } else {
        for (int i = indx; i < strlen(mailAddress); ++i) {
            if (mailAddress[i] == '.') {
                return true;
            }
        }
    }
}