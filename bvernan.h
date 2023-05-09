//
// Created by hamza on 12/06/2021.
//

#ifndef HAMZABRAHMI109429_BVERNAN_H
#define HAMZABRAHMI109429_BVERNAN_H

#include <stddef.h>

typedef struct Block_struct {
    int j_block;
    char* d_block;
} c_block;

typedef struct Key_struct {
    size_t length;
    char* key;
} t_key;

c_block * encode_block(c_block *block, const t_key* k, size_t size);

#endif //HAMZABRAHMI109429_BVERNAN_H
