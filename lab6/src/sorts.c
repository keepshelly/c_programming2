// sorts.c
#include "student.h"

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

// Вспомогательная функция для быстрой сортировки
void swap(struct Student* a, struct Student* b) {
    struct Student t = *a;
    *a = *b;
    *b = t;
}

// Функция разделения для быстрой сортировки
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

// Быстрая сортировка (QuickSort)
void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Сортировка подсчетом (Counting Sort)
void countingSort(struct Student arr[], int n) {
    int count[MAX_SCORE + 1] = {0};  // Используем макрос
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