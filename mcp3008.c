#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include "mcp3008.h"

#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_SPEED  1350000

static int spi_fd = -1;

int mcp3008_init() {
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        fprintf(stderr, "Failed to open SPI device %s\n", SPI_DEVICE);
        return -1;
    }

    uint8_t mode = SPI_MODE_0;
    uint8_t bits = 8;
    uint32_t speed = SPI_SPEED;

    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

    printf("MCP3008 SPI initialized on %s\n", SPI_DEVICE);
    return 0;
}

int mcp3008_read_raw(int channel) {
    if (spi_fd < 0) {
        fprintf(stderr, "SPI not initialized\n");
        return -1;
    }

    // MCP3008 needs 3 bytes: start bit, config, don't care
    uint8_t tx[3] = {
        0x01,                        // start bit
        (0x08 | channel) << 4,       // single mode + channel
        0x00                         // don't care
    };
    uint8_t rx[3] = {0, 0, 0};

    struct spi_ioc_transfer transfer = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 3,
        .speed_hz = SPI_SPEED,
        .bits_per_word = 8,
    };

    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) {
        fprintf(stderr, "SPI transfer failed\n");
        return -1;
    }

    // Result is in last 10 bits of rx
    int result = ((rx[1] & 0x03) << 8) | rx[2];
    return result;
}

float mcp3008_read_intensity(int channel) {
    int raw = mcp3008_read_raw(channel);
    if (raw < 0) return 0.5f; // fallback to default if error

    // Convert 0-1023 to 0.0-1.0
    float intensity = (float)raw / 1023.0f;
    printf("MCP3008 raw: %d  intensity: %.2f\n", raw, intensity);
    return intensity;
}

void mcp3008_close() {
    if (spi_fd >= 0) {
        close(spi_fd);
        spi_fd = -1;
    }
}