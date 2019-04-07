#include "trampoline.h"
#include "main.h"



Trampoline::Trampoline(float x, float y,float h,float l, color_t color) {
    float xt = -l/2;
    float yt = -h;
    float opp_x = xt+0.1;
    float opp_y = yt+h;
    GLfloat g_vertex_buffer_data1[18]={ 
         xt, opp_y, 0.0f,
         opp_x, opp_y, 0.0f,
         xt,  yt, 0.0f,
         xt,  yt, 0.0f,
         opp_x,  yt, 0.0f,
         opp_x, opp_y, 0.0f,            
    };
    xt=xt+l-0.1;
    opp_x=xt+0.1;
    opp_y=yt+h;
    GLfloat g_vertex_buffer_data2[18]={ 
         xt, opp_y, 0.0f,
         opp_x, opp_y, 0.0f,
         xt,  yt, 0.0f,
         xt,  yt, 0.0f,
         opp_x,  yt, 0.0f,
         opp_x, opp_y, 0.0f,            
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data2, color, GL_FILL);

    this->position = glm::vec3(x+l/2, y+h, 0);
    this->height = h;
    this->length = l;
    this->rotation = 0;
    
    float r = l/2;
    GLfloat g_vertex_buffer_data[542];
    float theta = 3.1416/60;
    float cur = 3.1416 ;

    for(int i=0;i<540;)
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

    this->object = create3DObject(GL_TRIANGLES,180, g_vertex_buffer_data, color, GL_FILL);
    
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object);    
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_tramp Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float h = this->height;
    float l = this->length;
    bounding_box_tramp bbox = { x, y, h, l};
    return bbox;
}
