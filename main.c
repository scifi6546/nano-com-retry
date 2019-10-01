#include "mmu.h"
#include "bus.h"
struct bus SYSTEM_BUS={0,0};
struct ram_bus MEMORY_BUS={0,0,0};
int main(){
	while(0==0){
		mmu_tick(&SYSTEM_BUS,&MEMORY_BUS);
	}
	return 0;
}

