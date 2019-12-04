#include <stdio.h>
#include "../bus.h"
#include "../logger.h"
#include <iostream>
#include <string>
void boot_dbg(){

}
int index=0;
#define NUM_STAGES 4
unsigned char mem_dbg_selected_device;
unsigned int mem_dbg_address;
unsigned char mem_dbg_read_or_write;
unsigned short mem_dbg_data;
char debug=1;
void dbg_tick(struct bus *in, struct ram_bus *foo){
	if(!debug){
		return;
	}
	if(in->device_select!=0){
		char buffer[80];
		sprintf(buffer,
			"bus device: 0x%x bus data: 0x%x",
			in->device_select,in->data);
	
		add_log(BUS_DBG,"dbg_tick",buffer);
	}
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
			break;
	}
	index++;
}
