//
// Created by hamza on 12/06/2021.
//

#include "bvernan.h"
#include <stdlib.h>

c_block * encode_block(c_block *block, const t_key* k, size_t size){
    int j = block->j_block;
    size_t n_k = k->length;

    char* al_block = malloc((size) * sizeof ( char));

    for (int i = 0,l = (int) n_k; i < size || l < i; i++) {
        al_block[i] = (char)(block->d_block[i] ^ k->key[(j + i) % n_k]);
    }
    block->d_block = al_block;
    return block;
}