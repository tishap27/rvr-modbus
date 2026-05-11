FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    libmodbus-dev \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY modbus_server.c mcp3008.c mcp3008.h serial_reader.c serial_reader.h Makefile ./

RUN make    

CMD ["./modbus_server"]