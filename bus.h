#ifndef BUS
#define BUS

struct bus{
	short data;
	char device_select;
}
struct ram_bus{
	short data_bus;
	short address_bus;
	char device_select;
	bool WRITE_OR_READ;
}
#define WRITE 0
#define READ 1
#endif
