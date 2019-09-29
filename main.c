#include "mmu.h"
#include "bus.h"
struct bus SYSTEM_BUS={0,0};
struct ram_bus MEMORY_BUS={0,0,0};
int main(){
	while(true){
		system_bus_tick();		
		ram_bus_tick();
		tick_counter++;
	}
	return 0;
}
int tick_counter=0;
void system_bus_tick(){
	if(tick_counter%2==0){
	//cpu_select_device();
	//cpu_sys_bus_tick()
	//device1_sysbus_tick();
	}else{
		//cpu_sys_bys_read();
		//device_sys_bus_read();
	}
}
void ram_bus_tick(){
	tick(&MEMORY_BUS);
	if(tick_counter%4==0){
		//device select
	}if(tick_counter%4==1){
		//address write
		//write WRITE or READ to device select
		//if write write data
	}if(tick_counter%4==2){
		//mmu read from bus stage
		//mmu write to bus
	}if(tick_counter%4==3){
		//device read from bus
	}
}

