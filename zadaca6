#include <stdio.h>
#include<string.h>
typedef struct Voz{
    char relacija[50];
    float km;
    int n;
}Voz;
typedef struct ZeleznickaStanica{
    char grad[20];
    Voz vozovi[30];
    int n;
}ZeleznickaStanica;
void read(ZeleznickaStanica *stanici,int n)
{
    for(int i=0;i<n;i++)
    {
        scanf(" %s %d",stanici[i].grad,&stanici[i].n);
        for(int j=0;j<stanici[i].n;j++)
        {
            scanf("%s %f %d",stanici[i].vozovi[j].relacija,&stanici[i].vozovi[j].km,&stanici[i].vozovi[j].n);

        }
    }
}
void najkratkaRelacija(ZeleznickaStanica *stanici,int n,char *grad)
{
    float minkm;
    int minj=0,mini=0;
    int flag=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<stanici[i].n;j++) {
          
        if (strcmp(stanici[i].grad,grad) == 0) {
            {
                if(flag==0)
                {
                minkm=stanici[i].vozovi[j].km;
                flag=1;
                }
            }
            
                if (stanici[i].vozovi[j].km <= minkm)
                {
                    minkm=stanici[i].vozovi[j].km;
                    minj=j;
                    mini=i;
                }
            
            }
        }
    }
    printf("Najkratka relacija: %s (%.0f km)",stanici[mini].vozovi[minj].relacija,stanici[mini].vozovi[minj].km);

}
int main()
{
    ZeleznickaStanica  stanici[100];
    int n;
    char grad[25];
    scanf("%d ",&n);
    read(stanici,n);
    scanf(" %s ",grad);
    najkratkaRelacija(stanici,n,grad);
    return 0;
}
