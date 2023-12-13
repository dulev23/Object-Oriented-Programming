#include<iostream>
#include<cstring>

using namespace std;

class WebPage {
private:
    char url[100]{};
    char *content;
public:
    WebPage(char *u = "", char *c = nullptr) {
        strcpy(url, u);
        content = new char[strlen(c) + 1];
        strcpy(content, c);
    }

    WebPage(const WebPage &webPage) {
        strcpy(url, webPage.url);
        content = new char[strlen(webPage.content) + 1];
        strcpy(content, webPage.content);
    }

    ~WebPage() {
        delete[]content;
    }

    WebPage &operator=(const WebPage &webPage) {
        if (this != &webPage) {
            delete[]content;
            strcpy(url, webPage.url);
            content = new char[strlen(webPage.content) + 1];
            strcpy(content, webPage.content);
        }
        return *this;
    }

    bool daliseIsti(WebPage p) {
        return strcmp(url, p.url) == 0;
    }

    friend class WebServer;
};

class WebServer {
private:
    char name[30]{};
    WebPage *webPage;
    int count;
public:
    WebServer(char *n = "", WebPage *webpage = nullptr, int count = 0) {
        strcpy(name, n);
        this->count = count;
        webPage = new WebPage[count];
        for (int i = 0; i < count; ++i) {
            webPage[i] = webpage[i];
        }
    }

    WebServer(const WebServer &webServer) {
        strcpy(name, webServer.name);
        count = webServer.count;
        webPage = new WebPage[count];
        for (int i = 0; i < count; ++i) {
            webPage[i] = webServer.webPage[i];
        }
    }

    ~WebServer() {
        delete[]webPage;
    }

    WebServer &operator=(const WebServer &webServer) {
        if (this != &webServer) {
            strcpy(name, webServer.name);
            count = webServer.count;
            delete[]webPage;
            webPage = new WebPage[count];
            for (int i = 0; i < count; ++i) {
                webPage[i] = webServer.webPage[i];
            }
        }
        return *this;
    }

    WebServer &addPage(WebPage p) {
        WebPage *tmp = new WebPage[count + 1]; //alocirame nova memorija
        for (int i = 0; i < count; ++i) {
            tmp[i] = webPage[i]; // smestuvame sodrzina od dinamicki alocirana niza vo novata temp. niza
        }
        tmp[count++] = p;
        delete[]webPage; //brisenje na niza
        webPage = tmp; //smestuvame sodrzina od temp.
        return *this;
    }

    WebServer &deletePage(const WebPage &webPage1) {
        int newCount = 0; //deklarirame i inicijalizirame nov counter = 0
        for (int i = 0; i < count; ++i) {
            if (!webPage[i].daliseIsti(webPage1)) { //ako ne se isti zgolemi go noviot counter
                newCount++;
            }
        }
        WebPage *tmp = new WebPage[newCount]; //alocirame nova memorija
        for (int i = 0; i < count; ++i) {
            if (!webPage[i].daliseIsti(webPage1)) {
                tmp[newCount++] = webPage[i];
            }
        }
        delete[]webPage; //brisenje na dinamicki alociranata niza
        webPage = tmp;
        count = newCount; //count atributot dobiva vrednost newCount deklariran i inkrementiram po izvrsuvanje na uslovite
        return *this;
    }

    void listPages() { //metod za printanje
        cout << "Number: " << count << endl;
        for (int i = 0; i < count; ++i) {
            cout << webPage[i].content << "- " << webPage[i].url << endl;
        }
    }
};

int main() {

    WebPage wp1("http://www.google.com", "The search engine");
    WebPage wp2("http://www.finki.ukim.mk", "FINKI");
    WebPage wp3("http://www.time.mk", "Site vesti");

    WebServer ws(" Server ");

    ws.addPage(wp1);
    ws.addPage(wp2);
    ws.addPage(wp3);

    ws.listPages();

    cout << "\nAfter delete: \n";
    ws.deletePage(wp3);

    ws.listPages();

    return 0;
}