#include "bus_io.h"
#include "logger.h"
#include <stdio.h>
#define BUFFER_SIZE 100
unsigned int num_ops_in_tick=0;
int buffer_index =-1;
struct buffer_item{
	unsigned short data=0;
	unsigned char device_id=0;
};
struct buffer_item bus_buffer[BUFFER_SIZE];
void buffer_bus(struct bus *in,unsigned short data,
		unsigned char device_id){
	if(buffer_index+1<BUFFER_SIZE){
		struct buffer_item temp;
		temp.data=data;
		temp.device_id=device_id;
		bus_buffer[buffer_index+1]=temp;
		buffer_index++;
	}
}
struct bus_result put_bus(struct bus *bus){
	struct bus_result res;
	if(num_ops_in_tick==0){
		if(buffer_index>=0){
			char buffer[80];
			sprintf(buffer,"putting 0x%x on bus to 0x%x",
					bus_buffer[buffer_index].data,
					bus_buffer[buffer_index].device_id);

			add_log(BUS_OPS,"put_bus",buffer);
			bus->data=bus_buffer[buffer_index].data;
			bus->device_select=bus_buffer[buffer_index].device_id;
			num_ops_in_tick++;
			buffer_index--;
			if(buffer_index<0){
				res.progress=BUS_RES_DONE;
				return res;
			}else{
				res.progress=BUS_RES_NOT_DONE;
				return res;
			}
		}else{
			res.progress=BUS_RES_DONE;
			return res;

		}
	}else{
		res.progress=BUS_RES_NOT_DONE;
		return res;
	}
}
void tick_bus(){
	num_ops_in_tick=0;
}
