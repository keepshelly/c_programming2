#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100
#define MAX_LINE_LENGTH 1024

void dict_init(Dictionary *dict) {
    dict->entries = malloc(INITIAL_CAPACITY * sizeof(DictEntry));
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
}

void dict_add(Dictionary *dict, const char *original, const char *translation) {
    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = realloc(dict->entries, dict->capacity * sizeof(DictEntry));
    }
    
    dict->entries[dict->size].original = strdup(original);
    dict->entries[dict->size].translation = strdup(translation);
    dict->size++;
}

const char *dict_find(const Dictionary *dict, const char *word) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].original, word) == 0) {
            return dict->entries[i].translation;
        }
    }
    return NULL;
}

void dict_free(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->entries[i].original);
        free(dict->entries[i].translation);
    }
    free(dict->entries);
}

bool dict_load(Dictionary *dict, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return false;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *sep = strchr(line, ' ');
        if (!sep) continue;
        
        *sep = '\0';
        char *translation = sep + 1;
        while (*translation == ' ') translation++;
        
        line[strcspn(line, "\n")] = '\0';
        translation[strcspn(translation, "\n")] = '\0';
        
        if (strlen(line) > 0 && strlen(translation) > 0) {
            dict_add(dict, line, translation);
        }
    }
    
    fclose(file);
    return true;
}