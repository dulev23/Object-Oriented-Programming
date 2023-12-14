#include<stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

typedef struct Date Date;

int compare(Date d1, Date d2) {
    if (d1.year > d2.year) {
        return 1;
    } else if (d1.year < d2.year) {
        return -1;
    } else {
        if (d1.month > d2.month) {
            return 1;
        } else if (d1.month < d2.month) {
            return -1;
        } else {
            if (d1.day > d2.day) {
                return 1;
            } else if (d1.day < d2.day) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}

void readDate(Date *d) {
    scanf("%d %d %d", &d->day, &d->month, &d->year);
}

void printDate(Date d) {
    printf("%02d.%02d.%d", d.day, d.month, d.year);
}

int main() {
    Date date;
    Date date1;
    readDate(&date);
    readDate(&date1);
    int result = compare(date, date1);
    if (result == 0) {
        printf("They are the same");
    } else if (result > 0) {
        printDate(date);
        printf(" is larger than ");
        printDate(date1);
    } else {
        printDate(date1);
        printf(" is larger than ");
        printDate(date);
    }
    return 0;
}