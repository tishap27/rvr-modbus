# Interface Control Document: rvr-modbus

Version 0.1 (draft)

## 1. Purpose
Defines the interfaces of the RVR Visibility Modbus Service: what it reads, what it publishes, and on which port.

## 2. Interfaces

| ID | Interface | Direction | Medium |
|----|-----------|-----------|--------|
| IF-1 | RVR input | In | Text lines on standard input |
| IF-2 | Light intensity | In | MCP3008 ADC over SPI (`/dev/spidev0.0`, channel 0) |
| IF-3 | RVR output | Out | Modbus TCP, port 1502 |

## 3. IF-1: RVR input
One line per report:

```
RVR:<value>
```

- `<value>` is in units of 100 ft. `RVR:12` means 1200 ft.
- Line ends with LF or CRLF.
- Lines that do not start with `RVR:` are ignored.

## 4. IF-2: Light intensity
- Potentiometer (0 to 5 V) read through an MCP3008, 10-bit.
- Counts (0 to 1023) are scaled to an intensity of 0.0 to 1.0.

## 5. Processing
```
adjusted = raw_ft * (1 + 0.25 * intensity)
```

## 6. IF-3: Modbus TCP output
- Server on port 1502, built with libmodbus.
- 10 holding registers (addresses 0 to 9).

| Address | Name | Encoding |
|---------|------|----------|
| 0 | Adjusted RVR | Feet, 16-bit unsigned |
| 1 | Low-visibility flag | 1 if raw RVR is below 1200 ft, else 0 |
| 2 to 9 | Unused | 0 |