#include "image.h"
#include "bus.h"
#include "gulkana.h"
#include "mendenhall.h"
int tick=0;
char x=0;
char y=0;
unsigned short index=0;
long num_draws=0;
char logo_index=0;
void boot_cpu(){
}
void cpu_tick(struct bus *sys_bus,struct ram_bus *in){
	if(tick%2==0){
		sys_bus->device_select=0x2;
		sys_bus->data=index; 
	}
	if(tick%2==1){
		unsigned short color =logo[index];
		if(logo_index%3==1)
			color=gulkana[index];
		if(logo_index%3==2)
			color=mendenhall[index];
		unsigned short duration = 1;
		sys_bus->data=(color<<12)+duration;
		index++;
		long temp_index=index;
		if(temp_index%(256*256)==0){
			num_draws++;
			if(num_draws%(1024)==0)
				logo_index++;
		}
	}
	tick++;
}
