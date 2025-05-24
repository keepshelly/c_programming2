// student.h
#ifndef STUDENT_H
#define STUDENT_H
#define MAX_SCORE 300
#define NAME_LENGTH 64

// Структура Student
struct Student {
    char name[NAME_LENGTH];
    int math;
    int phy;
    int inf;
    int total;
};

// Прототипы функций
struct Student addStudent(const char* name, int math, int phy, int inf);
void printStudentInfo(struct Student student);
void insertionSort(struct Student arr[], int n);
void countingSort(struct Student arr[], int n);
void quickSort(struct Student arr[], int low, int high);
double getTime();
void printCPUInfo();

#endif