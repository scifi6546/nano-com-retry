#include "render_public.h"
#include "camera_out.h"
int main(){
	initRenderP();
	float z=-1.0f;
	float a = 0.6f;
	Model screen(
		{glm::vec3(-1.0*a,-1.0*a,z),glm::vec3(1.0*a,-1.0*a,z),glm::vec3(1.0*a,1.0*a,z),glm::vec3(-1.08*a,1.0*a,z)}
		,{glm::vec2(0.0,1.0),glm::vec2(1.0,1.0),glm::vec2(1.0,0.0),glm::vec2(0.0,0.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});
    Text foo = genTextureP(std::string("test.png"));
	Mesh sc_mesh = genMesh(screen,foo,glm::vec3(0.0,0.0,0.0));
	while(0==0){
		/*
	screen = Model(
		{glm::vec3(-1.0,-1.0,z),glm::vec3(1.0,-1.0,z),glm::vec3(1.0,1.0,z),glm::vec3(-1.0,1.0,z)}
		,{glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec2(1.0,1.0),glm::vec2(-1.0,1.0)},
		{0,1,2,0,3,2},
		{glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});

		updateMeshP(screen,sc_mesh);
		*/
		drawMeshP(sc_mesh);
		drawRender(false);
	}

}
