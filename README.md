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
- systemd for service management

## Setup on Raspberry Pi

```bash
sudo apt install libmodbus-dev git
git clone https://github.com/tishap27/rvr-modbus
cd rvr-modbus
make
```

## Install as a System Service

```bash
sudo cp systemd/rvr-modbus.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable rvr-modbus
sudo systemctl start rvr-modbus
sudo systemctl status rvr-modbus
```

Service auto starts on boot and restarts automatically if it crashes.

## Running the Full System

On your laptop, pipe the simulator to the Pi over SSH:

```bash
python3 tests/sensor_simulator.py | ssh tisha@10.0.0.117 './rvr-modbus/modbus_server'
```

## RVR Protocol

Serial input format: `RVR:12` where 12 means 1200ft visibility.
Light intensity from MCP3008 adjusts the value: `adjusted = raw * (1 + 0.25 * intensity)`

## In Progress
- **Hardware integration** - MCP3008 ADC wiring; potentiometer light intensity input will replace simulated values
- **Low visibility alerting** - Modbus coil output when RVR drops below RVR12 (1200ft)
- **Error handling** - serial disconnect recovery, Modbus client timeout, malformed RVR frame detection
- **Testing** - unit tests for RVR parser and adjustment formula; sensor_simulator.py extended for edge cases (dropout, out-of-range values)
- **Calibration** - refining the light intensity adjustment coefficient (currently 0.25) against real runway lighting data
