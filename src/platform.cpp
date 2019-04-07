#include "platform.h"
#include "main.h"

Platform::Platform(float x, float y,float opp_x,float opp_y,color_t color) {
    this->rotation = 0;
     GLfloat g_vertex_buffer_data[18]={ 
         x, opp_y, 0.0f,
         opp_x, opp_y, 0.0f,
         x,  y, 0.0f,
         x,  y, 0.0f,
         opp_x,  y, 0.0f,
         opp_x, opp_y, 0.0f,            
    };
    

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
