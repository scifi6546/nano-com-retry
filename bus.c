struct bus{
	short data;
	char device_select;
}
struct bus SYSTEM_BUS={0,0};
struct bus MEMORY_BUS={0,0};
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
	if(tick_counter%3==0){
		//address select stage
	}if(tick_counter%3==1){
		//ram write to bus stage
	}if(tick_counter%3==2){
		//read from bus stage
	}
}
char RAM[0x10000];
void RAM_TICK(){

}

