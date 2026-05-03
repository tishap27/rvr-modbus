all:
	gcc -o modbus_server modbus_server.c -lmodbus

clean:
	rm -f modbus_server rvr
