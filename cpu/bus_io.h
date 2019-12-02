
#include "../bus.h"
#define BUS_RES_NOT_DONE 0
#define BUS_RES_DONE 1
struct bus_result{
	unsigned char progress=BUS_RES_NOT_DONE;
};
struct bus_result put_bus(struct sys_bus *bus,unsigned short data,unsigned char device_id);
