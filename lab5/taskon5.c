#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char destination[50]; // Название пункта назначения
    int train_number;     // Номер поезда
    int departure_hour;   // Час отправления
    int departure_minute; // Минута отправления
} Train;

//запись 
void write_trains_to_file(const char *filename, Train *trains, int n) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        exit(1);
    }
    fwrite(trains, sizeof(Train), n, file);
    fclose(file);
}

//чтение
Train* read_trains_from_file(const char *filename, int *n) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения!\n");
        exit(1);
    }
    // опред размера
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // кол-во записей
    *n = file_size / sizeof(Train);
    // памыять
    Train *trains = (Train*)malloc(file_size);
    if (trains == NULL) {
        printf("Ошибка выделения памяти!\n");
        fclose(file);
        exit(1);
    }
    //чтение из файла
    fread(trains, sizeof(Train), *n, file);
    fclose(file);
    return trains;
}
// функция для поиска поездов по полю
void search_trains(Train *trains, int n, int field, const char *value) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        int match = 0;
        switch (field) {
            case 1: // поиск по пункту
                if (strcmp(trains[i].destination, value) == 0) {
                    match = 1;
                }
                break;
            case 2: //номеру
                if (trains[i].train_number == atoi(value)) {
                    match = 1;
                }
                break;
            case 3: //времени 
                int hour, minute;
                sscanf(value, "%d:%d", &hour, &minute);
                if (trains[i].departure_hour == hour && trains[i].departure_minute == minute) {
                    match = 1;
                }
                break;
        }
        if (match) {
            printf("Поезд найден: %s, №%d, %02d:%02d\n",
                   trains[i].destination,
                   trains[i].train_number,
                   trains[i].departure_hour,
                   trains[i].departure_minute);
            found = 1;
        }
    }
    if (!found) {
        printf("Поезда с такими данными не найдены.\n");
    }
}
int main() {
    // запись данных в файл
    Train trains[] = {
        {"Москва", 123, 14, 30},
        {"Санкт-Петербург", 456, 17, 45},
        {"Новосибирск", 789, 9, 15}
    };
    int n = sizeof(trains) / sizeof(trains[0]);
    //  ф-ция запись данных в файл
    write_trains_to_file("Train.dat", trains, n);
    // чтение данных из файла
    int train_count;
    Train *loaded_trains = read_trains_from_file("Train.dat", &train_count);
    // запрос поля для поиска
    printf("По какому полю выполнить поиск?\n");
    printf("1. Пункт назначения\n");
    printf("2. Номер поезда\n");
    printf("3. Время отправления\n");
    int field;
    scanf("%d", &field);
    // запрос значения для поиска
    char value[50];
    printf("Введите значение для поиска: ");
    scanf("%s", value);
    search_trains(loaded_trains, train_count, field, value);
    free(loaded_trains);
    return 0;
}