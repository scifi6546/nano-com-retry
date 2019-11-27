#include "mem.h"
#include "logger.h"
#include <stdio.h>
#define DEVICE_SELECT 0x1
#define ADDRESS_WRITE 0x2
#define MMU_READ      0x3
#define DATA_READ     0x4
unsigned char memory_stage=DEVICE_SELECT;
struct mem_result load_mem(struct ram_bus *bus,unsigned int address){
	if(memory_stage==DEVICE_SELECT){
		memory_stage=ADDRESS_WRITE;
	}else if(memory_stage==ADDRESS_WRITE){
		bus->address_bus=address;
		bus->WRITE_OR_READ=READ;
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){
		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		printf("data read\n");
		memory_stage=DEVICE_SELECT;
		struct mem_result res;
		res.data = bus->data_bus;
		res.progress=RES_DONE;
		printf("returning: 0x%x\n",res.progress);
		printf("output data: 0x%x\n",res.data);
		return res;
	}
	struct mem_result res;
	return res;

}
//not done
struct mem_result write_mem(struct ram_bus *bus,unsigned int address,unsigned short data){
	if(memory_stage==DEVICE_SELECT){
		memory_stage=ADDRESS_WRITE;
	}else if(memory_stage==ADDRESS_WRITE){
		bus->WRITE_OR_READ=WRITE;
		bus->address_bus=address;
		bus->data_bus=data;
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){

		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		struct mem_result res;
		res.progress=RES_DONE;
		return res;
	}
	struct mem_result res;
	return res;
}
