# RVR Visibility Modbus Service

A simple aviation simulation system that reads Runway Visual Range (RVR) from serial input, adjusts it using ambient light sensor data, and publishes the result over Modbus TCP.

## Features
- Serial RVR input parsing
- Light intensity adjustment model
- Modbus TCP server output
- Designed for Raspberry Pi

## Tech Stack
- C (GCC)
- libmodbus
- Linux (systemd-ready)

## Build
```bash
sudo apt install libmodbus-dev
gcc -o modbus_server modbus_server.c -lmodbus
```

## Current Implementation
- Simulated real-time RVR data ingestion from sensor stream
- Environmental adjustment logic applied to raw visibility data
- Modbus TCP server exposing processed values via holding registers

## Hardware Setup (ATmega2560 to WSL)
```bash
# PowerShell as admin
usbipd list
usbipd bind --busid 1-2
usbipd attach --wsl --busid 1-2 --force
```
Then in WSL:
```bash
sudo chmod 666 /dev/ttyACM0
python3 modbus_server.py
```

## Status
In development
