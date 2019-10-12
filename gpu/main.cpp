#include "render_public.h"
#include "camera_out.h"
int main(){
	initRenderP();
	float z=-1.0f;
	float a = 0.6f;
	int width = 256;
	int height = 256;
	int num_comp = 4;
	unsigned char img[width*height*num_comp];
	for(int i=0;i<width*height*num_comp;i++){
		img[i]=i;
	}
	Model screen(
		{glm::vec3(-1.0*a,-1.0*a,z),glm::vec3(1.0*a,-1.0*a,z),glm::vec3(1.0*a,1.0*a,z),glm::vec3(-1.08*a,1.0*a,z)}
		,{glm::vec2(0.0,1.0),glm::vec2(1.0,1.0),glm::vec2(1.0,0.0),glm::vec2(0.0,0.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});
    Text foo = genTexturePVec(img,width,height,num_comp);
	Mesh sc_mesh = genMesh(screen,foo,glm::vec3(0.0,0.0,0.0));
	glm::vec3 pos(0.02,0.2,0.5);
	Camera cam(pos,0.0734f,1.5707f);
	while(0==0){
		/*
	screen = Model(
		{glm::vec3(-1.0,-1.0,z),glm::vec3(1.0,-1.0,z),glm::vec3(1.0,1.0,z),glm::vec3(-1.0,1.0,z)}
		,{glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec2(1.0,1.0),glm::vec2(-1.0,1.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});

		updateMeshP(screen,sc_mesh);
		 * 
		*/
		//pos.y+=0.001f;
		cam.setPos(pos);
		printf("y: %f\n",pos.y);
		cam.sendToRender();
		drawMeshP(sc_mesh);
		drawRender(false);
	}

}
