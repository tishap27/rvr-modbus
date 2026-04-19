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

## Current Implementation
- Simulated real-time RVR data ingestion from sensor stream
- Environmental adjustment logic applied to raw visibility data
- Modbus TCP server exposing processed values via holding registers

## Status
In development
