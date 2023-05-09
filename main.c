
#include <stdlib.h>
#include "IO_bvernan.h"

int main(int argc, char **argv) {
    if(argc<4)
    {
        fprintf(stderr,"Not enough arguments. Use: bvernan <Key filename> <Input filename> <Output filename>\n");
        exit(-1);
    }

    bvernan(argv[1],
            argv[2],
            argv[3]);
    return 0;
}
