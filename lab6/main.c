#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "student.h"

void printStudents(struct Student* students, int count) {
    printf("\n--- Список студентов ---\n");
    for (int i = 0; i < count; i++) {
        printStudentInfo(students[i]);
    }
    printf("-----------------------\n");
}

int main() {
    srand(time(NULL));
    printCPUInfo();

    // Тестируемые размеры данных (уменьшим для наглядности)
    int sizes[] = {5, 10};  // Было: 100, 10000, 100000
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int N = sizes[i];
        struct Student* students = malloc(N * sizeof(struct Student));

        // Генерация данных
        for (int j = 0; j < N; j++) {
            char name[NAME_LENGTH];
            snprintf(name, NAME_LENGTH, "Student%d", j + 1);
            students[j] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
        }

        printf("\nN = %d\n", N);
        printf("Размер данных: %.2f MB\n", (N * sizeof(struct Student)) / (1024.0 * 1024.0));

        // Вывод несортированного списка
        printf("\nНесортированный список:");
        printStudents(students, N);

        // Копия массива для сортировки
        struct Student* arr = malloc(N * sizeof(struct Student));
        memcpy(arr, students, N * sizeof(struct Student));

        // Тестирование сортировки
        double start = getTime();
        quickSort(arr, 0, N - 1);  // Используем QuickSort для примера
        double end = getTime();

        printf("\nОтсортированный список:");
        printStudents(arr, N);
        printf("QuickSort: %.4f сек\n", end - start);

        free(students);
        free(arr);
    }

    return 0;
}