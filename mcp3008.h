#ifndef MCP3008_H
#define MCP3008_H

// Initialize SPI connection to MCP3008
// Returns 0 on success, -1 on failure
int mcp3008_init();

// Read analog value from MCP3008 channel (0-7)
// Returns value 0-1023, or -1 on error
int mcp3008_read_raw(int channel);

// Read channel and convert to light intensity 0.0 - 1.0
float mcp3008_read_intensity(int channel);

// Close SPI connection
void mcp3008_close();

#endif