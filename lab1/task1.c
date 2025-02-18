#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define NAME_LENGTH 64

// Структура Student
struct Student {
    char name[NAME_LENGTH];
    int math;
    int phy;
    int inf;
    int total;
};

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

// Сортировка вставками (по убыванию)
void insertionSort(struct Student arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].total < key.total) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Сортировка подсчетом (Counting Sort)
void countingSort(struct Student arr[], int n) {
    const int MAX_SCORE = 300;
    int count[MAX_SCORE + 1] = {0};
    struct Student output[n];

    for (int i = 0; i < n; i++) 
        count[arr[i].total]++;

    for (int i = MAX_SCORE - 1; i >= 0; i--)
        count[i] += count[i + 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Быстрая сортировка (QuickSort)
void swap(struct Student* a, struct Student* b) {
    struct Student t = *a;
    *a = *b;
    *b = t;
}

int partition(struct Student arr[], int low, int high) {
    int pivot = arr[high].total;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].total >= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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

int main() {
    srand(time(NULL));
    printCPUInfo();

    // Тестируемые размеры данных
    int sizes[] = {100, 10000, 100000};
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

        // Копия массива для разных сортировок
        struct Student* arr1 = malloc(N * sizeof(struct Student));
        struct Student* arr2 = malloc(N * sizeof(struct Student));
        struct Student* arr3 = malloc(N * sizeof(struct Student));
        memcpy(arr1, students, N * sizeof(struct Student));
        memcpy(arr2, students, N * sizeof(struct Student));
        memcpy(arr3, students, N * sizeof(struct Student));

        // Тестирование сортировок
        double start, end;

        // Сортировка вставками
        start = getTime();
        insertionSort(arr1, N);
        end = getTime();
        printf("InsertionSort: %.4f сек\n", end - start);

        // Сортировка подсчетом
        start = getTime();
        countingSort(arr2, N);
        end = getTime();
        printf("CountingSort:  %.4f сек\n", end - start);

        // Быстрая сортировка
        start = getTime();
        quickSort(arr3, 0, N - 1);
        end = getTime();
        printf("QuickSort:     %.4f сек\n", end - start);

        free(students);
        free(arr1);
        free(arr2);
        free(arr3);
    }

    return 0;
}