#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "dictionary.h"

bool translate_file(const char *input_file, const Dictionary *dict, const char *output_file);

#endif