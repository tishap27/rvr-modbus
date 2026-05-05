all:
	gcc -o modbus_server modbus_server.c mcp3008.c serial_reader.c -lmodbus

clean:
	rm -f modbus_server