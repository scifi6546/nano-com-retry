#ifndef RENDER_PUBLIC
#define RENDER_PUBLIC
#include <glm/glm.hpp>
#include <string>
#include <vector>
/*
this contains the public interface for rendering info
*/
struct Text{
    int id=-1;
    int width = 0;
    int height = 0;
};
/*
This contains polygonial data to be sent to rendering engine
*/
class Model{
    
    public:
        std::vector<glm::vec3> pos;//position
        std::vector<glm::vec2> texCoord;//texture chordinates
        std::vector<unsigned int> indices;
        std::vector<glm::vec3> normal;
             
        Model(std::vector<glm::vec3> pos,//position
            std::vector<glm::vec2> texCoord,//texture chordinates
            std::vector<unsigned int> indices,std::vector<glm::vec3> normal){
                this->pos = pos;
                this->texCoord=texCoord;
                this->indices=indices;
                this->normal=normal;
                
                
        }
        Model(std::string in);
        void add(Model to_add,glm::vec3 pos);
        Model(){

        }
    private:
};
/*
Simple struct for telling what to draw
*/
class Mesh{
    public:
        int id=-1;//id for refrencing mesh items
        glm::vec3 pos;//position to draw the mesh at
        Text texture_use;//what texture to use when drawing the mesh
        //Mesh();


};

/*
Not Implemented or tested
initizes rendering engine
*/
void initRenderP();
/*
 * Generates texture from image data
*/
Text genTexturePVec(unsigned char* imagedata,int width,int height,int num_components);
/*
Not Tested
makes texture will get rid of p conflists with genTexture from texture.cpp
*/
Text genTextureP(std::string file_name);
/*
NOT IMPLEMENTED OR TESTED
Draws all draw calls asked for
*/
void drawRender(bool reset_mouse);
/*
Not Tested
generates the mesh from the model
*/
Mesh genMesh(Model in,Text texture,glm::vec3 pos);
/*
Not Tested or Implemented
generates the mesh from .obj at filename
*/
Mesh genMesh(std::string file_name,Text texture,glm::vec3 pos);

/*
Not Tested
updates a sekected mesh and changes it
*/
void updateMeshP(Model in, Mesh &toUpdate);

/*
checks if mesh is actually valid
*/
bool isMeshValid(Mesh in);
/*
Not Tested
quits rendring engine
*/
void quitRender();
/*
Not Tested
draws mesh (eventually)
*/
void drawMeshP(Mesh in);
/*
Not tested or implemented 
Deletes mesh specified
*/
void deleteMeshP(Mesh &in);
/*
Draws the mesh for the gui
*/
void drawMeshGui(Mesh in);
#endif
