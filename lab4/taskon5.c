#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_word(char *word) {
    int length = strlen(word);
    for (int i = 0; i < length / 2; i++) {
        char temp = word[i];
        word[i] = word[length - i - 1];
        word[length - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <файл>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Ошибка создания выходного файла");
        fclose(input_file);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            reverse_word(word);
            fprintf(output_file, "%s ", word);
            word = strtok(NULL, " \t\n");
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

    printf("Обработка завершена. Результат записан в output.txt\n");
    return 0;
}