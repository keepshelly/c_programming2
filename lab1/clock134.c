#include <time.h>

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

    // Замер времени выполнения CountingSort
    clock_t start = clock();
    countingSort(students, N);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Вывод времени выполнения и размера данных
    printf("N = %d\n", N);
    printf("Время выполнения CountingSort: %f секунд\n", time_spent);
    printf("Размер данных: %lu байт\n", N * sizeof(struct Student));
    printf("\n");
}

int main() {
    srand(time(NULL));

    // Замер времени для разных N
    measureSortingTime(100);
    measureSortingTime(10000);
    measureSortingTime(100000);

    return 0;
}