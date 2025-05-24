#include "dictionary.h"
#include "translator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.txt dictionary.txt output.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    Dictionary dict;
    dict_init(&dict);

    if (!dict_load(&dict, argv[2])) {
        fprintf(stderr, "Failed to load dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!translate_file(argv[1], &dict, argv[3])) {
        fprintf(stderr, "Translation failed\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    dict_free(&dict);
    return EXIT_SUCCESS;
}