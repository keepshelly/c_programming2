// student_utils.c
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Создание студента
struct Student addStudent(const char* name, int math, int phy, int inf) {
    struct Student newStudent;
    snprintf(newStudent.name, NAME_LENGTH, "%s", name);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

// Вывод информации о студенте
void printStudentInfo(struct Student student) {
    printf("Имя: %-10s | Математика: %3d | Физика: %3d | Информатика: %3d | Сумма: %3d\n",
           student.name, student.math, student.phy, student.inf, student.total);
}

// Замер времени выполнения
double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Вывод информации о процессоре
void printCPUInfo() {
    printf("\nИнформация о процессоре:\n");
    system("grep 'model name' /proc/cpuinfo | uniq");
    system("grep 'cpu MHz' /proc/cpuinfo | uniq");
    printf("\n");
}