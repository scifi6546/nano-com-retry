#include "mmu.h"

int counter=0;
void device_select(ram_bus* in){
	in->device_select=0x0;//cpu id
}
void bus_read(ram_bus *in){
	if(in->WRITE_OR_READ==WRITE){
		//setup get values to write
	}
	if(in->WRITE_OR_READ==READ){
		//setup stuf to read
	}
}
void bus_write(ram_bus *in){

}
void tick(ram_bus *in){
	if(tick_counter%4==0){
		device_select(in);
	}
	if(tick_counter%4==2){
		bus_read(in);
	}
	counter++;
}
