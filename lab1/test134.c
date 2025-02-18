#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 64
#define MAX_SCORE 300

// Структура Student
struct Student {
    char name[NAME_LENGTH];
    int math;
    int phy;
    int inf;
    int total;
};

// Функция для создания нового студента
struct Student addStudent(const char* name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, NAME_LENGTH - 1);
    newStudent.name[NAME_LENGTH - 1] = '\0'; // Убедимся, что строка завершается нулевым символом
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

// Функция для вывода информации о студенте
void printStudentInfo(struct Student student) {
    printf("Имя: %s\n", student.name);
    printf("Оценка по математике: %d\n", student.math);
    printf("Оценка по физике: %d\n", student.phy);
    printf("Оценка по информатике: %d\n", student.inf);
    printf("Общий балл: %d\n", student.total);
    printf("\n");
}

// CountingSort для сортировки студентов по общему баллу
void countingSort(struct Student students[], int size) {
    int count[MAX_SCORE + 1] = {0};
    struct Student output[size];

    // Подсчет количества студентов с каждым общим баллом
    for (int i = 0; i < size; i++) {
        count[students[i].total]++;
    }

    // Преобразование count[i] в позицию элемента в выходном массиве
    for (int i = 1; i <= MAX_SCORE; i++) {
        count[i] += count[i - 1];
    }

    // Построение выходного массива
    for (int i = size - 1; i >= 0; i--) {
        output[count[students[i].total] - 1] = students[i];
        count[students[i].total]--;
    }

    // Копирование отсортированного массива обратно в students
    for (int i = 0; i < size; i++) {
        students[i] = output[i];
    }
}

// Функция для замера времени выполнения сортировки
void measureSortingTime(int N) {
    struct Student students[N];

    // Заполнение массива студентов случайными данными
    for (int i = 0; i < N; i++) {
        char name[NAME_LENGTH];
        snprintf(name, NAME_LENGTH, "Student%d", i + 1);
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }

    // Вывод студентов до сортировки (для N <= 100)
    if (N <= 100) {
        printf("Студенты до сортировки (N = %d):\n", N);
        for (int i = 0; i < N; i++) {
            printStudentInfo(students[i]);
        }
    }

    // Замер времени выполнения CountingSort
    clock_t start = clock();
    countingSort(students, N);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Вывод студентов после сортировки (для N <= 100)
    if (N <= 100) {
        printf("\033[91mСтуденты после сортировки (N = %d):\033[0m\n", N);
        for (int i = 0; i < N; i++) {
            printStudentInfo(students[i]);
        }
    }

    // Вывод времени выполнения и размера данных
    printf("N = %d\n", N);
    printf("Время выполнения CountingSort: %f секунд\n", time_spent);
    printf("Размер данных: %lu байт\n", N * sizeof(struct Student));
    printf("\n");
}

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Вывод информации о процессоре
    printf("Информация о процессоре:\n");
    system("cat /proc/cpuinfo | grep 'model name' | uniq");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | uniq");
    printf("\n");

    // Замер времени для разных значений N
    measureSortingTime(100);
    measureSortingTime(10000);
    measureSortingTime(100000);

    return 0;
}
/*void insertionSort(struct Student students[], int size) {
    for (int i = 1; i < size; i++) {
        struct Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].total < key.total) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}*/