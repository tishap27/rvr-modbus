
import sys
import threading
from pymodbus.server import StartTcpServer
from pymodbus.datastore import ModbusServerContext, ModbusSlaveContext, ModbusSequentialDataBlock

LIGHT_INTENSITY = 0.5

def parse_rvr(line):
    line = line.strip()
    if not line.startswith("RVR:"):
        return None
    try:
        return float(line[4:])
    except ValueError:
        return None

def adjust_rvr(raw, intensity):
    return raw * (1 + 0.25 * intensity)

store = ModbusSlaveContext(
    hr=ModbusSequentialDataBlock(1, [0] * 10)
)

context = ModbusServerContext(slaves=store, single=True)

def read_loop():
    for line in sys.stdin:
        raw = parse_rvr(line)
        if raw is None:
            print("Invalid input")
            continue

        adjusted = adjust_rvr(raw * 100, LIGHT_INTENSITY)
        register_value = int(adjusted)

        store.setValues(3, 1, [register_value])  # 3 = holding register

        print("Raw RVR:", raw * 100, "ft")
        print("Adjusted RVR:", round(adjusted, 2), "ft")
        print("Modbus register 0:", register_value)

thread = threading.Thread(target=read_loop, daemon=True)
thread.start()

print("Modbus TCP server running on port 1502")
StartTcpServer(context=context, address=("0.0.0.0", 1502))