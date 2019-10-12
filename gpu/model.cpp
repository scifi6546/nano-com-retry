#include "render_public.h"
#include "obj_loader.h"
void Model::add(Model to_add,glm::vec3 pos){
    this->pos.reserve(this->pos.size()+to_add.pos.size());
    this->texCoord.reserve(this->texCoord.size()+to_add.texCoord.size());
    int size = this->pos.size();
    for(int i =0;i<to_add.pos.size();i++){
        this->pos.push_back(to_add.pos[i]+pos);
        this->texCoord.push_back(to_add.texCoord[i]);
    }

    for(int i =0;i<to_add.indices.size();i++){
        this->indices.push_back(to_add.indices[i]+size);
    }
    for(int i =0;i<to_add.normal.size();i++){
        this->normal.push_back(to_add.normal[i]);
    }
}
Model::Model(std::string in){
    objl::Loader loader;
    loader.LoadFile(in);
    this->indices=loader.LoadedIndices;
    for(int i=0;i<loader.LoadedVertices.size();i++){
        float x,y,z;
        x=loader.LoadedVertices[i].Normal.X;
        y=loader.LoadedVertices[i].Normal.Y;
        z=loader.LoadedVertices[i].Normal.Z;
        this->normal.push_back(glm::vec3(x,y,z));

        x=loader.LoadedVertices[i].Position.X;
        y=loader.LoadedVertices[i].Position.Y;
        z=loader.LoadedVertices[i].Position.Z;
        this->pos.push_back(glm::vec3(x,y,z));

        x=loader.LoadedVertices[i].TextureCoordinate.X;
        y=loader.LoadedVertices[i].TextureCoordinate.Y;
        this->texCoord.push_back(glm::vec2(x,y));
    }
}