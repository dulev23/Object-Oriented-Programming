#include<stdio.h>

typedef struct Laptop {
    char Firma[100];
    float monitor;
    int touch;
    int cena;
} Laptop;

typedef struct ITStore {
    char ime[100];
    char lokacija[100];
    Laptop laptop[100];
    int broj;
} ITStore;

void readitstore(ITStore *salon, int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %d", salon[i].ime, salon[i].lokacija, &salon[i].broj);
        for (int j = 0; j < salon[i].broj; ++j) {
            scanf("%s %f %d %d", salon[i].laptop[j].Firma, &salon[i].laptop[j].monitor, &salon[i].laptop[j].touch,
                  &salon[i].laptop[j].cena);
        }
    }
}

void printitstore(ITStore *salon, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%s %s\n", salon[i].ime, salon[i].lokacija);
        for (int j = 0; j < salon[i].broj; ++j) {
            printf("%s %g %d\n", salon[i].laptop[j].Firma, salon[i].laptop[j].monitor, salon[i].laptop[j].cena);
        }
    }
}

void najeftina_ponuda(ITStore *niza, int n) {
    int najdobarcena = 1000000, najdobarJ, maxI;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < niza[i].broj; ++j) {
            if (niza[i].laptop[j].cena < najdobarcena && niza[i].laptop[j].touch == 1) {
                najdobarcena = niza[i].laptop[j].cena;
                najdobarJ = j;
                maxI = i;
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata: \n"
           "%s %s\n", niza[maxI].ime, niza[maxI].lokacija);
    printf("Najniskata cena iznesuva: %d", niza[maxI].laptop[najdobarJ].cena);
}

int main() {
    int n;
    ITStore niza[100];
    scanf("%d", &n);
    readitstore(niza, n);
    printitstore(niza, n);
    najeftina_ponuda(niza, n);
    return 0;
}