#include<stdio.h>
#include<time.h>
#include <stdlib.h> // INCLUIE srand() e rand()
#include "rnd.h"

void setup_random() {
    srand((unsigned int)time(NULL));
}

int random_number(int max) {
    if (max == 0) return 0; // protecao basica pra nao dividir por zero
    return rand() % max ;
}

Orientation random_orientation() {
    int val = rand() % 2;
    if (val == 0) {
        return ORIENT_H;
    } else {
        return ORIENT_V;
    }
}
}
