#include "display.h"
#include "render_manager.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"
#include "error.h"
const int display_height = 1000;
const int display_width = 1000;

int getHeight(){return display_height;}
int getWidth(){return display_width;}
unsigned int frameBufferFBO;
unsigned int frameBufferTex;//depth map texture
unsigned int mainBufferFBO;
render_target *bound_shader;//currently bound shader
//render_target *gameWorld_ptr;
GLenum error;
template<typename T1, typename T2,typename T3>
class triplet{
    public:
        triplet(T1 first,T2 second,T3 third){
            _a=first;
            _b=second;
            _c=third;};
        T1 a(){return _a;};
        T2 b(){return _b;};
        T3 c(){return _c;};
    private:
        T1 _a;
        T2 _b;
        T3 _c;
};
/*
Contains all draw calls to be drawn in frame
*/
std::vector<triplet<RunTimeModel,glm::vec3,Texture>> Draw_Calls;
std::vector<triplet<RunTimeModel,glm::vec3,Texture>> Draw_Calls_Gui;
Model buffer=Model(
    {glm::vec3(1.0,1.0,0.1),glm::vec3(1.0,-1.0,0.1),
     glm::vec3(-1.0,-1.0,0.1),glm::vec3(-1.0,1.0,0.1)},
        
    {glm::vec2(1.0f,1.0f),glm::vec2(1.0,0.0f),
        glm::vec2(0.0f,0.0f),glm::vec2(0.0f,1.0)},{0,1,3,1,2,3},
    {glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,1.0)});
RunTimeModel buffer_model;

render_target *getBoundShader(){
    return bound_shader;
}
void rManager::makeFBO(render_target &in){
    
    getError();
    glGenFramebuffers(1,&in.bufer_object.FBO_OJECT);
    printf("in_fbo_object: %i",in.bufer_object.FBO_OJECT);
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);
    in.bufer_object.attTexture=genTextureEmp();
    getError();

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,in.bufer_object.attTexture.color_texture,0);
    getError();

    //creating depth map
    //glGenTextures(1,&in.bufer_object.DEPTH_MAP);
    //glBindTexture(GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP);

    //glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,800,600,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);
    //getError();
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,in.bufer_object.attTexture.depth_texture,0);
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
    //    GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP,0);
    
    //glBindTexture(GL_TEXTURE_2D,0);
    getError();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    getError();
    
}
//todo check if gameWorld is active
void sendAmbientInfo(glm::vec3 color,GLfloat intensity,
    glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color){
        render_target * temp = getBoundShader();
        printf("render_target ptr: %p\n",temp);
        getError();
        sendVec3("ambient_color",color,*getBoundShader());
        getError();
        sendGLfloat("ambient_intensity",intensity,*getBoundShader());
        getError();
        sendVec3("sun_pos",sun_pos,*getBoundShader());
        getError();
        sendGLfloat("sun_intensity",sun_intensity,*getBoundShader());
        getError();
        sendVec3("sun_color",sun_color,*getBoundShader());
        getError();
}
void sendPos(glm::vec3 pos){
    getError();
    sendVec3("pos_global",pos,*getBoundShader());
    getError();
}
void bufferDrawCalls(RunTimeModel Model,glm::vec3 pos,Texture texture){
    Draw_Calls.push_back(triplet<RunTimeModel,glm::vec3,Texture>(Model,pos,texture));
}
void bufferDrawCallsGui(RunTimeModel Model,glm::vec3 pos,Texture texture){
    Draw_Calls_Gui.push_back(triplet<RunTimeModel,glm::vec3,Texture>(Model,pos,texture));
}
void rManager::RuseShader(render_target &in){
    useShader(in);
    bound_shader=&in;
}
void rManager::bindFBO(render_target in){

    getError();
    if(error!=0){
        printf("glError (before binding)!!!\n\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);//Error on this line!
    //printf("FBO OBJECT: %i\n",in.FBO_OJECT);
    getError();
    if(error!=0){
        printf("glError (after binding)!!!\n\n");
    }
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
        printf("framebuffer incomplete error!\nerror!\n");
    //printf("bound buffer (after binding): %i ",in);
}
render_target gameWorld;//game world will be rendered to here
render_target bufferWorld;//Buffer shader
void initRender(){
    //unsigned int *inFBO = new unsigned int[2];
    //glGenFramebuffers(2,inFBO);
    //getError();
    initDisplay(display_width,display_height,"temp_title");
    //gameWorld_ptr=&gameWorld;
    

    //shaderInit();
    
    getError();
    createShaderT({"gpu/shaders/shader.vs","gpu/shaders/shader.fs"},gameWorld);
    createShaderT({"gpu/shaders/buffer_shader.vs","gpu/shaders/buffer_shader.fs"},bufferWorld);
    getError();
    rManager::RuseShader(gameWorld);
    getError();
    initCam(60.0,display_width,display_height,.01,500);
    getError();
    rManager::makeFBO(gameWorld);
    std::vector<RunTimeModel> in = initMesh({buffer});
    buffer_model=in[0];
    getError();
    rManager::RuseShader(gameWorld);
    
}
void drawFrame(bool reset_mouse){
    //glBindFramebuffer(GL_FRAMEBUFFER,0);
    //rManager::bindFBO(gameWorld);
    //useGameShader();
    getError();
    rManager::bindFBO(gameWorld);
    rManager::RuseShader(gameWorld);
    sendShader();
    getError();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    getError();
    //clearDisplay(0.0,.1,.6,1.0);
    
    //drawMesh(buffer_model,glm::vec3(1.0,100.0,0.0));
    for(int i =0;i<Draw_Calls.size();i++){
        bindTexture(Draw_Calls[i].c(),gameWorld,"diffuse");
        drawMesh(Draw_Calls[i].a(),Draw_Calls[i].b());
    }
    Draw_Calls.clear();
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    //rManager::bindFBO(bufferWorld);
    
    rManager::RuseShader(bufferWorld);
    bindTexture(gameWorld.bufer_object.attTexture,bufferWorld,"diffuse");
    drawMesh(buffer_model,glm::vec3(0.0f,0.0f,0.5f));
    for(int i =0;i<Draw_Calls_Gui.size();i++){
        bindTexture(Draw_Calls_Gui[i].c(),bufferWorld,"diffuse");
        drawMesh(Draw_Calls_Gui[i].a(),Draw_Calls_Gui[i].b());
    }
    Draw_Calls_Gui.clear();
    //glGetIntegerv(GL_FRAMEBUFFER_BINDING,&in);
    //printf("bound buffer (after rendering): %i\n",in);
    
    getError();
    
    //glBindFramebuffer(GL_FRAMEBUFFER,0);
    //useShader(bufferWorld);
    //useFrameCam();
    //bindTexture(gameWorld.bufer_object.attTexture,gameWorld,"diffuse");
    
    //drawMeshBuffer(buffer_model,glm::vec3(1.0,100.0,0.0));
    updateDisplay();
    
    error=glGetError();
}
void sendCamera(glm::vec3 position,float thetax,float thetay){
    getError();
    translateCam(position,thetax,thetay);
    getError();
}
void quitRender_INT(){
    delDisplay();
}
void printUnis(){

}
