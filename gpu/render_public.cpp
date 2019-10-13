#include "render_public.h"
#include "render_manager.h"
#include "mesh.h"
#include "texture.h"
#include <utility>
//NOT TO BE EXPOSED TO END USER
template<typename T1, typename T2>
class good_pair{
    public:
        good_pair(T1 first,T2 second){
            _a=first;
            _b=second;};
        T1 a(){return _a;};
        T2 b(){return _b;};
		void setA(T1 a){_a=a;};
		void setB(T2 b){_b=b;};
    private:
        T1 _a;
        T2 _b;
};

/*
A vector containing all runtime models and accociated id's
The first element is id second is runtime model
*/
std::vector<good_pair<int,RunTimeModel>> Models;
/*
A vector containing all textures and associated id's
The first element is the id and the second is associated texture
The id's are ascending order
*/
std::vector<good_pair<int,Texture>> Textures;
/*
This inserts a texture into the Textures vec
*/
Text insertTexture(Texture in){
    int new_id = Textures.size();
    
    Textures.push_back(good_pair<int,Texture>(new_id,in));
    Text out;
    out.id=new_id;
    return out;
}
Texture getTexture(Text in){
    //if(in.id!=0)
    //    printf("in.id: %i\n",in.id);
    return Textures[in.id].b();
}
void setTexture(Text set,Texture set_to){
	Textures[set.id].setB(set_to);
}
/*
Checks the integreity of the texture vector
*/
bool checkTextInteg(){
    int last_id = Textures[0].a();
    //int last_id = std::get<0>(Textures[0]);
    for(int i=0;i<Textures.size();i++){
        int new_id = Textures[i].a();
        if(new_id!=last_id+1){
            return false;
        }
        last_id=new_id;
    }
    return true;
}
/*
This Inserts a mesh into the Models vector
*/
Mesh insertMesh(RunTimeModel in){
    unsigned int new_id = Models.size();
    Models.push_back(good_pair<int,RunTimeModel>(new_id,in));
    Mesh out;
    out.id=new_id;
    return out;
}
/*
This gets a model from the Models vector
*/
RunTimeModel getModel(Mesh in){
    return Models[in.id].b();
}
void initRenderP(){
    initRender();
}
void drawRender(bool reset_mouse){
    drawFrame(reset_mouse);
}
void quitRender(){
    quitRender_INT();
}
Text genTextureP(std::string filename){
    Texture temp = genTexture(filename);
    printf("\ntemp.texture: %i ",temp.color_texture);
    Text out = insertTexture(temp);
    printf("temp.id: %i \n",out.id);
    out.height=temp.height;
    out.width=temp.width;

    return out;
}

Text genTexturePVec(unsigned char* imagedata,int width,int height,int num_components){
	Texture temp = genTextureVec(imagedata,width,height,num_components);
    Text out = insertTexture(temp);
    printf("temp.id: %i \n",out.id);
    out.height=temp.height;
    out.width=temp.width;

    return out;
}
Text updateTexturePVec(Text edit,unsigned char* imagedata,int width,int height,int num_components){
	Texture temp = getTexture(edit);
	temp = updateTextureVec(temp,imagedata,width,height,num_components);
	setTexture(edit,temp);
}
Mesh genMesh(Model in,Text texture,glm::vec3 pos){
    RunTimeModel temp = initMesh({in})[0];
    Mesh out = insertMesh(temp);
    out.texture_use=texture;
    out.pos=pos;
    return out;
}
Mesh genMesh(std::string file_name,Text texture,glm::vec3 pos){
    Model temp_model = Model(file_name);
    //printf("temp_model num poly's %i\n",temp_model.indices.size());
    RunTimeModel temp = initMesh({temp_model})[0];
    Mesh out = insertMesh(temp);
    out.texture_use=texture;
    out.pos=pos;
    return out;
}
bool isMeshValid(Mesh in){
    if(in.id<0){
        return false;
    }
    return true;
}
void drawMeshP(Mesh in){
    Texture temp = getTexture(in.texture_use);
    bufferDrawCalls(getModel(in),in.pos,temp);
}
void updateMeshP(Model in, Mesh &toUpdate){
    std::vector<RunTimeModel> temp;
    temp.push_back(getModel(toUpdate));
    updateMesh({in},temp);
}
void deleteMeshP(Mesh &in){
    std::vector<RunTimeModel> temp;
    temp.push_back(getModel(in));
    deleteMesh(temp);
    in.id=-1;
}
void drawMeshGui(Mesh in){
    Texture temp = getTexture(in.texture_use);
    bufferDrawCallsGui(getModel(in),in.pos,temp);
}
