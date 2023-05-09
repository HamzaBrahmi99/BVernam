//
// Created by hamza on 12/06/2021.
//

#ifndef HAMZABRAHMI109429_IO_BVERNAN_H
#define HAMZABRAHMI109429_IO_BVERNAN_H
#include "bvernan.h"
#include <stdio.h>
typedef struct Struct_data_source {
    FILE* file;
} source;

t_key* load_key(char* file);

source *load_source(char *file, char *mode);

void read_from_input(const t_key *loaded_key, source *input, source *output);

void write_in_output_file(source *output, size_t read, c_block *al_block);

void bvernan(char* keyfile, char* input_file, char* output_file);
#endif //HAMZABRAHMI109429_IO_BVERNAN_H
