#include "plank.h"
#include "main.h"


float rand_FloatRange2(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

Plank::Plank(float x, float y,float r, color_t color) {
    this->position = glm::vec3(x, y, 1);
    float angle = rand_FloatRange2(-45,45);
    this->rotation = angle;
    this->radius = r;
    this->colour = color;
    speed = 0.05;
    GLfloat g_vertex_buffer_data[10000];
    float theta = M_PI/100.0;
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
    float xt = -2*r;
    float yt = r;
    float opp_y =r+0.2;
    float opp_x = 2*r ;
    GLfloat g_vertex_buffer_data1[18]={ 
         xt, opp_y, 0.0f,
         opp_x, opp_y, 0.0f,
         xt,  yt, 0.0f,
         xt,  yt, 0.0f,
         opp_x,  yt, 0.0f,
         opp_x, opp_y, 0.0f,            
    };
    this->object1 = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data1, COLOR_BRICK, GL_FILL);
    
}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    
}

void Plank::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plank::tick() {
    this->position.x += speed;
    if(this->position.x>20)
    {
        float p = rand_FloatRange2(-30,-8);
        float q = rand_FloatRange2(0,5);
        
        this->position.x=p;   
        this->position.y=q;
    }
    // this->position.y -= speed;
}

bounding_box_t Plank::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float r = this->radius+0.1;
    bounding_box_t bbox = { x, y, r };
    return bbox;
}
