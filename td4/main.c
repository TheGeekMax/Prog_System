#include <stdio.h>
#include <stdlib.h>
#include "exo12.h"

int main(int argc, char const *argv[]){
    if(argc == 3){
        exo122(atoi(argv[1]), atoi(argv[2]));
    }

    exo123(10);
    exo124();

    return 0;
}
