#include "error.h"
#include <stdio.h>
#include <GL/glew.h>
int glError=0;
void getError(){
    glError=glGetError();
    if(glError!=0){
        printf("glError: %i\n\n",glError);
    }
}
