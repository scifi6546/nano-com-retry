#include "mmu.h"
#include "bus.h"
#include "gpu/gpu.h"
#include "cpu/cpu.h"
#include <unistd.h>
struct bus SYSTEM_BUS={0,0};
struct ram_bus MEMORY_BUS={0,0,0};
int main(){
	mmu_boot();
	boot_cpu();
	boot_gpu();
	while(0==0){
		cpu_tick(&SYSTEM_BUS,&MEMORY_BUS);
		gpu_tick(&SYSTEM_BUS,&MEMORY_BUS);
		mmu_tick(&SYSTEM_BUS,&MEMORY_BUS);
	//	usleep(10);
	}
	return 0;
}

