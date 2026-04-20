#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <modbus/modbus.h>

#define LIGHT_INTENSITY 0.5f
#define MODBUS_PORT 1502
#define REGISTER_COUNT 10

float parse_rvr(const char *line) {
    char buffer[128];
    strncpy(buffer, line, sizeof(buffer));
    buffer[strcspn(buffer, "\r\n")] = 0;

    if (strncmp(buffer, "RVR:", 4) != 0) {
        return -1;
    }

    return atof(buffer + 4);
}

float adjust_rvr(float raw, float intensity) {
    return raw * (1.0f + 0.25f * intensity);
}

int main() {
    modbus_t *ctx;
    modbus_mapping_t *mapping;
    int server_socket;
    int client_socket;

    ctx = modbus_new_tcp("0.0.0.0", MODBUS_PORT);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create Modbus context\n");
        return 1;
    }

    mapping = modbus_mapping_new(0, 0, REGISTER_COUNT, 0);
    if (mapping == NULL) {
        fprintf(stderr, "Failed to create Modbus mapping\n");
        modbus_free(ctx);
        return 1;
    }

    server_socket = modbus_tcp_listen(ctx, 1);
    if (server_socket == -1) {
        fprintf(stderr, "Failed to listen on port %d\n", MODBUS_PORT);
        modbus_mapping_free(mapping);
        modbus_free(ctx);
        return 1;
    }

    printf("Modbus TCP server running on port %d\n", MODBUS_PORT);

    client_socket = modbus_tcp_accept(ctx, &server_socket);

    char line[128];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        float raw = parse_rvr(line);
        if (raw < 0) {
            printf("Invalid input\n");
            continue;
        }

        float raw_ft = raw * 100.0f;
        float adjusted = adjust_rvr(raw_ft, LIGHT_INTENSITY);
        int register_value = (int)adjusted;

        mapping->tab_registers[0] = register_value;

        printf("Raw RVR: %.1f ft\n", raw_ft);
        printf("Adjusted RVR: %.1f ft\n", adjusted);
        printf("Modbus register 0: %d\n", register_value);

        modbus_reply(ctx, (uint8_t[]){0}, 0, mapping);
    }

    modbus_mapping_free(mapping);
    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}