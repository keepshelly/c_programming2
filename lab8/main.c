#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Изменяем тип возвращаемого значения на int
int run_program() {
    struct node* head1 = NULL;
    struct node* head2 = NULL;
    int input, n;

    printf("Введите количество элементов верхнего списка: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Список не может быть пустым!\n");
        return 1; // Возвращаем код ошибки
    }

    printf("Введите элементы верхнего списка:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &input) != 1) {
            freeList(head1);
            return 1;
        }
        append(&head1, input);
    }

    printf("Введите количество элементов нижнего списка: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Список не может быть пустым!\n");
        freeList(head1);
        return 1;
    }

    printf("Введите элементы нижнего списка:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &input) != 1) {
            freeList(head1);
            freeList(head2);
            return 1;
        }
        append(&head2, input);
    }

    struct node* current = head1;
    int isUpperList = 1;
    char command;

    while (1) {
        printf("\nТекущий элемент: %d\n", current->data);
        printf("Введите команду:\n[S/s] Переключиться в нижний список\n[D/d] Вперед\n[Q/q] Выход\n> ");
        
        if (scanf(" %c", &command) != 1) {
            freeList(head1);
            freeList(head2);
            return 1;
        }

        switch (command) {
            case 'D': case 'd':
                if (current->next) current = current->next;
                else printf("Достигнут конец списка!\n");
                break;

            case 'S': case 's':
                if (isUpperList) {
                    int pos = 0;
                    struct node* tmp = head1;
                    while (tmp != current) {
                        tmp = tmp->next;
                        pos++;
                    }
                    
                    struct node* lower = head2;
                    for (int i = 0; i < pos && lower != NULL; i++) {
                        lower = lower->next;
                    }
                    
                    if (lower) {
                        current = lower;
                        isUpperList = 0;
                        printf("Переключено на нижний список\n");
                    } else {
                        printf("Нет соответствующего элемента в нижнем списке!\n");
                    }
                } else {
                    printf("Уже в нижнем списке!\n");
                }
                break;

            case 'Q': case 'q':
                freeList(head1);
                freeList(head2);
                return 0; // Успешное завершение

            default:
                printf("Некорректная команда!\n");
        }
    }
}

int main() {
    return run_program(); // Передаем код возврата из run_program
}