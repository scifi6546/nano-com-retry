#include "mmu.h"
#include <stdio.h>
#define RAM_MAX_ADDRESSIBLE 0xffff
int counter=0;
char selected_device=0x0;
char read_or_write=0x0;
unsigned int address=0x0;
short data_write = 0x0;
unsigned char ram[RAM_MAX_ADDRESSIBLE+1];


void mmu_boot(){
	FILE *p = fopen("boot.rom","r");
	for(int i =0;i<RAM_MAX_ADDRESSIBLE+1;i++){
		char t = fgetc(p);
		if(t!=EOF)
			ram[i]=t;
		else
			ram[i]=0;
	}
	fclose(p);
}
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
	}
}
void bus_write(struct ram_bus *in){
	if(read_or_write==READ){
		printf("address red: 0x%x\n",address);
		in->data_bus=ram[address];	
	}
	if(read_or_write==WRITE){

		ram[address&0xFFFFFF0000000000]=data_write;
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
	if(counter%4==3){

	}
	counter++;
}
