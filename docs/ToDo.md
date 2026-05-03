# TODO

## Hardware
-

## Software
- [ ] Replace hardcoded LIGHT_INTENSITY with real ADC read
- [ ] Add low visibility warning when RVR < 12 (below 1200 ft)
- [ ] Write systemd service file for auto start on boot
- [ ] Write Dockerfile to containerize the service
- [ ] Deploy on K3s across two Pi nodes for redundancy
- [ ] Test failover — kill master, confirm worker picks up

- [ ] Encrypt Modbus output (TLS)
- [ ] Second Pi as redundant node via K3s

## Done
- [x] Serial RVR input parsing in C
- [x] Custom RVR protocol (RVR:12 format)
- [x] Light intensity adjustment formula
- [x] Modbus TCP server in C using libmodbus
- [x] Tested with ATmega2560 over UART
- [x] Tested with fake simulator
- [x] Makefile for build