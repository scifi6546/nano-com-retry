#include "image.h"
#include "bus.h"
#include "gulkana.h"
int tick=0;
char x=0;
char y=0;
unsigned short index=0;
void boot_cpu(){
}
void cpu_tick(struct bus *sys_bus,struct ram_bus *in){
	if(tick%2==0){
		sys_bus->device_select=0x2;
		sys_bus->data=index; 
	}
	if(tick%2==1){
		unsigned short color =gulkana[index];
		unsigned short duration = 1;
		sys_bus->data=(color<<12)+duration;
		index++;
	}
	tick++;
}
