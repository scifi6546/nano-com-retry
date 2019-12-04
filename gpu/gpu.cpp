#include <thread>
#include <mutex>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include "rendering_lib/render_public.h"
#include "gpu.h"
#include "../logger.h"
std::mutex mtx;
const int width = 256;
const int height = 256;
const int num_comp = 4;
unsigned char img[width*height*num_comp];
Mesh sc_mesh;
Text texture;

class GpuMemory{
	public:
		GpuMemory(){
			for(int i=0;i<0xFFFF;i++){
				_mem[i]=0x0;
			}
		}
		void setMem(unsigned short addr, 
				char color){
			//making sure that color is inside of bit size
			assert(color<=0xF);
			_mem[addr]=color;
		}
		void _sendToDisplay(){
			for(int i =0;i<256*256;i++){
				int color = _colorTable[_mem[i]];
				char r = color>>16;
				char g = (color^0xFF00FF)>>8;
				char b = color^0xFFFF00;
				img[i*4]=r;
				img[i*4+1]=g;
				img[i*4+2]=b;
				//alpha
				img[i*4+3]=0x00;

			}

		}
	private:
 		unsigned char _mem[256*256];
		const int _colorTable[0x10] = 
			{
				0x000000,0x444444,
				0x000088,0x4444BB,
				0x008800,0x44BB44,
				0x008888,0x44BBBB,

				0x880000,0xBB4444,
				0x880088,0xBB44BB,
				0x888800,0xBB44BB,
				0x888888,0xBBBBBB,
			};

};
GpuMemory vram;
void draw_thread(){
	mtx.lock();
	initRenderP();
	float z=0.5f;
	float a=0.5f;
	for(int i=0;i<width*height*num_comp;i++){
		img[i]=i;
	}
	Model screen(
		{glm::vec3(-1.0f,-1.0f,z),
		glm::vec3(0.6f,-1.0f,z),
		glm::vec3(0.6f,0.2f,z),
		glm::vec3(-1.0f,0.2f,z)}
		,{
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(0.0f,1.0f),
		glm::vec2(0.0f,0.0f)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0f,0.0f,0.0f)});
    texture = genTexturePVec(img,width,height,num_comp);
	sc_mesh = genMesh(screen,texture,glm::vec3(0.0,0.0,0.0));
	mtx.unlock();
	while(0==0){
		mtx.lock();
		//pos.y+=0.001f;
		vram._sendToDisplay();
		//cam.setPos(pos);
		updateTexturePVec(texture,img,256,256,4);
		//cam.sendToRender();
		drawMeshP(sc_mesh);
		drawRender(false);
		mtx.unlock();
		usleep(16666);

	}
}
int boot_gpu(){
	std::thread draw(draw_thread);
	draw.detach();
	return 0;
}

//actual emulation code
char x_axis = 0;
char y_axis = 0;
unsigned short addr=0;
char color = 0;
unsigned char draw_duration = 0;
const char device_id = 0x02;
int cycle_num=0;
static char img_disp=0;
void gpu_tick(bus *sys_bus, ram_bus *mem_bus){
		mtx.lock();
	if(sys_bus->device_select==device_id){
		unsigned short data_in = sys_bus->data;
		if(cycle_num%2==0){
			addr=data_in;
			char buffer[80];
			sprintf(buffer,"getting address: 0x%x",addr);
			add_log(GPU_INFO,"gpu_tick",buffer);
		
		}else if(cycle_num%2==1){
			color = data_in>>12;
			draw_duration = data_in&0x000F;
			char buffer[80];
			sprintf(buffer,"putting color 0x%x at addr 0x%x raw_data: 0x%x",color,addr,data_in);
			add_log(GPU_INFO,"gpu_tick",buffer);
			
				for(unsigned char i=0;
						i<draw_duration;i++){
					vram.setMem(i+ addr,color);
			}
		}
		cycle_num++;
	}
	sys_bus->device_select=0;
	sys_bus->data=0;
		mtx.unlock();
}
