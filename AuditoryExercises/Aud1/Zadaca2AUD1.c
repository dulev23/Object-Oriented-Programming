#include<stdio.h>
#include<ctype.h>
#include<string.h>

struct Student {
    char firstName[100];
    char lastName[100];
    char index[10];
    int grades[40];
    int countGrade;
};

typedef struct Student Student;

void readStudent(Student *s) {
    scanf("%s%s%s %d", s->firstName, s->lastName, s->index, &s->countGrade);
    for (int i = 0; i < s->countGrade; ++i) {
        scanf("%d", &s->grades[i]);
    }
}

void normalizeName(char *name) {
    name[0] = toupper(name[0]);
    for (int i = 1; i < strlen(name); ++i) {
        name[i] = tolower(name[i]);
    }
}

float average(Student s) {
    float sum = 0;
    for (int i = 0; i < s.countGrade; ++i) {
        sum += s.grades[i];
    }
    return sum / s.countGrade;
}

void printStudent(Student s) {
    normalizeName(s.firstName);
    normalizeName(s.lastName);
    printf("%s %s %s %.2f", s.firstName, s.lastName, s.index, average(s));
}

int main() {
    Student s;
    readStudent(&s);
    printStudent(s);
    return 0;
}