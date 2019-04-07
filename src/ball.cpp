#include "ball.h"
#include "main.h"


float rand_FloatRange1(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

Ball::Ball(float x, float y,float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = r;
    this->colour = color;
    speed = 0.05;
    GLfloat g_vertex_buffer_data[10000];
    float theta = 3.1416/100;
    float cur = 0;
    for(int i=0;i<9999;)
    {
        if(i%9==0)
        {
            g_vertex_buffer_data[i++] = 0.0f;
            g_vertex_buffer_data[i++] =  0.0f;
            g_vertex_buffer_data[i++]=0.0f;
        }
        else
        {
            g_vertex_buffer_data[i++]= (r*cos(cur));
            g_vertex_buffer_data[i++]= (r*sin(cur));
            g_vertex_buffer_data[i++]=0.0f;
            g_vertex_buffer_data[i++]= (r*cos(cur+theta));
            g_vertex_buffer_data[i++]= (r*sin(cur+theta));
            g_vertex_buffer_data[i++]=0.0f;
            cur+=theta;
        }

    }

    this->object = create3DObject(GL_TRIANGLES, 3333, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += speed;
    if(this->position.x>20)
    {
        float p = rand_FloatRange1(-30,-8);
        float q = rand_FloatRange1(0,5);
        
        this->position.x=p;   
        this->position.y=q;
    }
    // this->position.y -= speed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float r = this->radius;
    bounding_box_t bbox = { x, y, r };
    return bbox;
}
