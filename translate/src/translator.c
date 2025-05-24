#include "translator.h"
#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

static bool is_word_char(int c) {
    return isalpha(c) || c == '\'' || (c & 0x80);
}

bool translate_file(const char *input_file, const Dictionary *dict, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return false;
    }

    int c;
    char word[MAX_WORD_LENGTH] = {0};
    int pos = 0;
    bool in_word = false;

    while ((c = fgetc(input)) != EOF) {
        if (c == EOF) break;
        
        if (is_word_char(c)) {
            if (!in_word && pos > 0) {
                // Если слово прервано (например, апострофом), продолжаем
                word[pos++] = c;
            } else if (pos < MAX_WORD_LENGTH - 1) {
                word[pos++] = c;
            }
            in_word = true;
        } else {
            if (in_word) {
                word[pos] = '\0';
                const char *translation = dict_find(dict, word);
                if (translation) {
                    fputs(translation, output);
                } else {
                    fputs(word, output);
                }
                pos = 0;
                in_word = false;
            }
            fputc(c, output); // Записываем пробел/перенос как есть
        }
    }

    // Обработка последнего слова
    if (in_word) {
        word[pos] = '\0';
        const char *translation = dict_find(dict, word);
        fputs(translation ? translation : word, output);
    }

    fclose(input);
    fclose(output);
    return true;
}