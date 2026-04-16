#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "serial_reader.h"

float read_rvr_from_serial(const char *device) {
    (void)device;

    char buffer[128];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -2;  // EOF sentinel
    }

    buffer[strcspn(buffer, "\r\n")] = 0;

    if (strncmp(buffer, "RVR:", 4) != 0) {
        return -1;  // bad parse
    }

    char *value_str = buffer + 4;
    while (*value_str == ' ') value_str++;

    return atof(value_str) * 100.0f;
}