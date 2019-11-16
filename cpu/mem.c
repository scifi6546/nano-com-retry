#include "mem.h"

#define DEVICE_SELECT 0x1
#define ADDRESS_WRITE 0x2
#define MMU_READ      0x3
#define DATA_READ     0x4
unsigned char memory_stage=DEVICE_SELECT;
struct mem_result load_mem(struct ram_bus *bus,unsigned int address){
	switch(memory_stage){
		case DEVICE_SELECT:{
			memory_stage=ADDRESS_WRITE;
			break;
		}
		case ADDRESS_WRITE:{
			bus->address_bus=address;
			bus->WRITE_OR_READ=READ;
			memory_stage=MMU_READ;
			break;
		}
		case MMU_READ:{
			memory_stage=DATA_READ;
			break;
		}
		case DATA_READ:{
			memory_stage=DEVICE_SELECT;
			struct mem_result res;
			res.data = bus->data_bus;
			res.progress=DONE;
			return res;
		}

	}
	struct mem_result res;
	return res;

}
