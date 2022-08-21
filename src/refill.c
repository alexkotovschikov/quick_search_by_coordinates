#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include "short.h"

int main() {
    FILE *output = NULL;
    output = fopen("arrayB.bin", "wb+");
    if (output != NULL) {
        refil_file(output, 300000);
        fclose(output);
    }
    output = fopen("arrayA.bin", "wb+");
    if (output != NULL) {
        refil_file(output, 1000);
        fclose(output);
    }
    return 0;
}
