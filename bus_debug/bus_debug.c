#include <stdio.h>
#include "../bus.h"
void boot_dbg(){

}
int index=0;
#define NUM_STAGES 4
unsigned char mem_dbg_selected_device;
unsigned int mem_dbg_address;
unsigned char mem_dbg_read_or_write;
unsigned short mem_dbg_data;
void dbg_tick(struct bus *in, struct ram_bus *foo){
	switch (index%4){
		case 0:
			mem_dbg_selected_device=foo->device_select;
			break;
		case 1:
			mem_dbg_address = foo->address_bus;
			mem_dbg_read_or_write=foo->WRITE_OR_READ;
			break;
		case 2:
			break;
		case 3:
			mem_dbg_data=foo->data_bus;
			printf("address: %x data_returned: %x\n",mem_dbg_address,mem_dbg_data);
			break;
	}
	index++;
}
