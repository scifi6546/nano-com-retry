#include "render_public.h"
#include "camera_out.h"
int main(){
	initRenderP();
	float z=-1.0f;
	Model screen(
		{glm::vec3(-1.0,-1.0,z),glm::vec3(1.0,-1.0,z),glm::vec3(1.0,1.0,z),glm::vec3(-1.0,1.0,z)}
		,{glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec2(1.0,1.0),glm::vec2(-1.0,1.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});
    Text foo = genTextureP(std::string("test.png"));
	Mesh sc_mesh = genMesh(screen,foo,glm::vec3(0.0,0.0,0.0));
	Camera cam(glm::vec3(0.0f,0.0f,0.0f),0.0,90.0);
	while(0==0){
		z+=0.01f;
	printf("z: %f\n",z);
	screen = Model(
		{glm::vec3(-1.0,-1.0,z),glm::vec3(1.0,-1.0,z),glm::vec3(1.0,1.0,z),glm::vec3(-1.0,1.0,z)}
		,{glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec2(1.0,1.0),glm::vec2(-1.0,1.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});
		updateMeshP(screen,sc_mesh);
		drawMeshP(sc_mesh);
		cam.sendToRender();
		drawRender(false);
	}

}
