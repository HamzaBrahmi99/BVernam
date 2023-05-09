//
// Created by hamza on 12/06/2021.
//

#include "IO_bvernan.h"
#include <stdlib.h>

c_block *allocate_block(size_t size, int j);

c_block *allocate_block(size_t size, int j) {
    c_block *al_block = malloc(sizeof(c_block));
    if (al_block == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for a block\n");
        exit(-1);
    }
    al_block->d_block = malloc(size * sizeof(char));
    if (al_block->d_block == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for d_block\n");
        exit(-1);
    }
    al_block->j_block = j;
    return al_block;
}

t_key *read_key(source *key_source);

t_key *read_key(source *key_source) {
    fseek(key_source->file, 0, SEEK_END);
    size_t f_size = (size_t) ftell(key_source->file);
    fseek(key_source->file, 0, SEEK_SET);
    t_key *allocated_key = malloc(sizeof(t_key));
    if (allocated_key == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for the allocated_key\n");
        exit(-1);
    }
    allocated_key->key = malloc(f_size * sizeof(char));
    allocated_key->length = f_size;
    char *key_buffer = malloc((int) (f_size) * sizeof(char));
    if (key_buffer == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for a key_buffer\n");
        exit(-1);
    }
    size_t read;
    read = fread(key_buffer, sizeof(char), f_size, key_source->file);
    if (read < 0) {
        fprintf(stderr, "ERROR - Failed to read from the key");
        exit(-1);
    }
    allocated_key->key = key_buffer;
    return allocated_key;
}

t_key *load_key(char *file) {
    source *allocated_source = malloc(sizeof(source));
    if (allocated_source == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for a source\n");
        exit(-1);
    }
    allocated_source->file = fopen(file, "rb");
    if (allocated_source->file == NULL) {
        fprintf(stderr, "ERROR - Failed to open the key file for reading\n");
        exit(-1);
    }
    t_key *key_buffer = read_key(allocated_source);
    fclose(allocated_source->file);
    return key_buffer;
}

source *load_source(char *file, char *mode) {
    source *allocated_source = malloc(sizeof(source));
    if (allocated_source == NULL) {
        fprintf(stderr, "ERROR - Failed to memory for allocated_source");
        exit(-1);
    }
    allocated_source->file = fopen(file, mode);
    if (allocated_source->file == NULL) {
        fprintf(stderr, "ERROR - Failed to open the output file for reading\n");
        exit(-1);
    }
    return allocated_source;
}

void write_in_output_file(source *output, size_t read, c_block *al_block) {
    fwrite(al_block->d_block, sizeof(char), read, output->file);
}

c_block *read_from_file(const t_key *loaded_key, source *input, source *output, size_t read, int j, size_t k,
                        char *block_buffer);

c_block *read_from_file(const t_key *loaded_key, source *input, source *output, size_t read, int j, size_t k,
                        char *block_buffer) {
    c_block *al_block = allocate_block(k, 0);
    while ((read = fread(block_buffer, sizeof(char), k, input->file)) > 0) {
        al_block->j_block = j;
        al_block->d_block = block_buffer;
        al_block = encode_block(al_block, loaded_key, read);
        write_in_output_file(output, read, al_block);
        j++;
    }
    return al_block;
}

void read_from_input(const t_key *loaded_key, source *input, source *output) {
    size_t read = 0;
    int j = 0;
    size_t k = loaded_key->length;
    char *block_buffer = malloc(k * sizeof(char));
    if (block_buffer == NULL) {
        fprintf(stderr, "ERROR - Failed to allocate memory for block_buffer\n");
        exit(-1);
    }

    if (k < 1) {
        int a;
        while ((a = getc(input->file)) != EOF) {
            putc(a, output->file);
        }
        return;
    }

    c_block *al_block = read_from_file(loaded_key, input, output, read, j, k, block_buffer);

    free(block_buffer);
    block_buffer = NULL;
    free(al_block->d_block);
    al_block->d_block = NULL;
    free(al_block);
    al_block = NULL;
}

void bvernan(char *keyfile, char *input_file, char *output_file) {
    t_key *loaded_key = load_key(keyfile);
    source *input = load_source(input_file, "rb");
    source *output = load_source(output_file, "wb");

    read_from_input(loaded_key, input, output);

    fclose(input->file);
    fclose(output->file);

    free(loaded_key->key);
    loaded_key->key = NULL;
    free(loaded_key);
    loaded_key = NULL;
    free(output);
    output = NULL;
    free(input);
    input = NULL;

}