
#include "../bus.h"
#define BUS_RES_NOT_DONE 0
#define BUS_RES_DONE 1
//puts data onto bufer to be written max 100 elements
void buffer_bus(struct bus *in,unsigned short data, unsigned char device_id);
struct bus_result{
	unsigned char progress=BUS_RES_NOT_DONE;
};
struct bus_result put_bus(struct bus *bus);
void tick_bus();
