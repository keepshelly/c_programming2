#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

typedef struct {
    char *original;
    char *translation;
} DictEntry;

typedef struct {
    DictEntry *entries;
    int size;
    int capacity;
} Dictionary;

void dict_init(Dictionary *dict);
void dict_add(Dictionary *dict, const char *original, const char *translation);
const char *dict_find(const Dictionary *dict, const char *word);
void dict_free(Dictionary *dict);
bool dict_load(Dictionary *dict, const char *filename);

#endif