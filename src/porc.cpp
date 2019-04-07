#include "porc.h"
#include "main.h"



Porc::Porc(float x, float y,float h,float l, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->height = h;
    this->length = l;
    speed = 0.01;
    GLfloat g_vertex_buffer_data[]={ 
         0, 0, 0.0f,
         l, 0, 0.0f,
         l/2,  h, 0.0f,
         l, 0, 0.0f,
         2*l, 0, 0.0f,
         l+l/2,  h, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Porc::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porc::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porc::tick() {
    
    if(this->position.x + 2*this->length >=-3.0 && this->position.x + 2*this->length <-2)
    {
        speed = -speed;
    }
    else if(this->position.x <-8)
    {

        speed = -speed;
    }
    else if(this->position.x < 1 && this->position.x  > 0)
    {
        speed= -speed;
    }
    else if(this->position.x + 2*this->length >=5)
        speed = -speed;
    this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_porc Porc::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float r = this->height;
    float l = this->length;
    bounding_box_porc bbox = { x, y, r ,l};
    return bbox;
}
