#include <stdio.h>

void sort(int arr[], int n) {
    // Ваша функция сортировки
}

int main() {
    int a[] = {4, 2};
    int n = sizeof(a) / sizeof(a[0]);
    sort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
