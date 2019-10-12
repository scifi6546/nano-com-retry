#include "mmu.h"
#define RAM_MAX_ADDRESSIBLE 0xffff
int counter=0;
char selected_device=0x0;
char read_or_write=0x0;
short address=0x0;
short data_write = 0x0;
char ram[0x10000];
void device_select(struct ram_bus* in){
	selected_device=0x0;
	in->device_select=selected_device;//cpu id
	
}
void bus_read(struct ram_bus *in){
	if(in->WRITE_OR_READ==WRITE){
		read_or_write=WRITE;
		address=in->address_bus;
		data_write=in->data_bus;
	}
	if(in->WRITE_OR_READ==READ){
		read_or_write=READ;
		address=in->address_bus;
		//setup stuf to read
	}
}
void bus_write(struct ram_bus *in){
	if(read_or_write==READ){
		in->data_bus=ram[address];	
	}
	if(read_or_write==WRITE){
		ram[address]=data_write;
	}
}
//systembus not needed but used for completness sake
void mmu_tick(struct bus *foo,struct ram_bus *in){
	if(counter%4==0){
		device_select(in);
	}
	if(counter%4==2){
		bus_read(in);
		bus_write(in);
	}
	counter++;
}
