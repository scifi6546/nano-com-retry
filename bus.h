#ifndef BUS
#define BUS

struct bus{
	short data;
	char device_select;
};
struct ram_bus{
	short data_bus;
	unsigned int address_bus;
	char device_select;
	char WRITE_OR_READ;
};
#define WRITE 0
#define READ 1
#endif
