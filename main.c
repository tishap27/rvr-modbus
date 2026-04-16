#include <stdio.h>
#include <stdlib.h>
#include "serial_reader.h"

int main() {
    printf("Starting RVR simulation system...\n");

    while (1) {
        float rvr = read_rvr_from_serial(NULL);

        if (rvr == -2) {
            printf("End of input, exiting.\n");
            break;  // EOF - clean exit
        } else if (rvr < 0) {
            printf("Invalid input\n");
        } else {
            printf("RVR value: %.2f ft\n", rvr);
        }
    }

    return 0;
}