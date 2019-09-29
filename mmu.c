#include "mmu.h"
ram_bus tick(ram_bus *in){
	if(tick_counter%4==0){
		return device_select(in);
	}
	if(tick_counter%4==2){
		return bus_read(in);
	}
	counter++;
}
