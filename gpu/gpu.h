#ifndef GPU_H
#define GPU_H
#include "../bus.h"
int boot_gpu();
void gpu_tick(bus *sys_bus, ram_bus *mem_bus);
#endif
