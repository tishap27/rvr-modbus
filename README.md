# RVR Visibility Modbus Service

A software service that monitors Runway Visual Range (RVR) inputs and updates the RVR value by adjusting based on ambient light conditions. Built for Raspberry Pi 3B+ as part of a real-time aviation ground operations system.

## What It Does

Reads serial RVR data, adjusts the value based on runway light intensity from an analog sensor, and publishes the result over Modbus TCP on port 1502. When RVR drops below 1200ft (RVR12), the airport enters low visibility operations.

## Hardware

- Raspberry Pi 3B+
- MCP3008 ADC chip (analog light intensity input via SPI)
- Potentiometer (simulates runway light intensity 0-5V)
- Laptop running sensor simulator (serial RVR input)

## Tech Stack

- C with libmodbus
- Raspberry Pi OS 32-bit
- SPI via Linux spidev

## Setup on Raspberry Pi

```bash
sudo apt install libmodbus-dev git
git clone https://github.com/tishap27/rvr-modbus
cd rvr-modbus
make
./modbus_server
```

## Running the Full System

On your laptop, pipe the simulator to the Pi over SSH:

```bash
python3 tests/sensor_simulator.py | ssh tisha@10.0.0.117 './rvr-modbus/modbus_server'
```

## RVR Protocol

Serial input format: `RVR:12` where 12 means 1200ft visibility.
Light intensity from MCP3008 adjusts the value using: `adjusted = raw * (1 + 0.25 * intensity)`

## Project Status

Core service running on Raspberry Pi 3B+. MCP3008 wiring pending, Systemd service and low visibility warning in progress.
