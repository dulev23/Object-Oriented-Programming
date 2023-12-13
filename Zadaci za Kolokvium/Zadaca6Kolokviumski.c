#include<stdio.h>
#include<string.h>

typedef struct Voz {
    char relacija[50];
    float km;
    int brPatnici;
} Voz;

typedef struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int brVozovi;
} ZeleznickaStanica;

void readZeleznickaStanica(ZeleznickaStanica *stanica, int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", stanica[i].grad, &stanica[i].brVozovi);
        for (int j = 0; j < stanica[i].brVozovi; ++j) {
            scanf("%s %f %d", stanica[i].vozovi[j].relacija, &stanica[i].vozovi[j].km, &stanica[i].vozovi[j].brPatnici);
        }
    }
}

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    float minkm = 0;
    int minj = 0, mini = 0;
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < zs[i].brVozovi; ++j) {
            if (strcmp(zs[i].grad, grad) == 0) {
                if (flag == 0) {
                    minkm = zs[i].vozovi[j].km;
                    flag = 1;
                }
            }
            if (zs[i].vozovi[j].km <= minkm) {
                minkm = zs[i].vozovi[j].km;
                minj = j;
                mini = i;
            }
        }
    }
    printf("Najkratka relacija: %s (%.0f km)", zs[mini].vozovi[minj].relacija, zs[mini].vozovi[minj].km);
}

int main() {
    int n;
    scanf("%d", &n);
    ZeleznickaStanica zs[100];
    readZeleznickaStanica(zs, n);
    char grad[25];
    scanf("%s", grad);
    najkratkaRelacija(zs, n, grad);
    return 0;
}