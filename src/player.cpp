#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.5;
    speed_x = 0.0;
    speed_y = 0.0;
    gravity = -0.006;
    deaccn = 0.003;
    level = 1 ;
    score = 0 ;
    GLfloat g_vertex_buffer_data[10000];
    float theta = 3.1416/100;
    float cur = 0;
    float r = 0.5;
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

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    // this->position.x -= speed_x;
    if(this->position.x>=-2.5 && this->position.x<=.5 )
    {
        if(this->position.y<-1.51)
        {
            if(sqrt(pow(this->position.x+1,2)+pow(this->position.y+2,2))>1.5)
            {
                if(this->position.x<-1)
                {
                    this->position.x+=0.005;
                    this->position.y = -sqrt(pow(1.5,2)-pow(this->position.x+1,2))-2; 

                }
                else if(this->position.x>-1)
                {
                    this->position.x-=0.005;
                    this->position.y = - sqrt(pow(1.5,2)-pow(this->position.x+1,2))-2; 
                }

            }
            else
            {     
                speed_y=-0.012;
                this->position.y+=speed_y;
            }
        }
        else
        {
            speed_y+=gravity;
            this->position.x += speed_x;    
            this->position.y += speed_y;
        }
    }   
    else
    { 
        
        if(this->position.y>=-1.50)
        {
            speed_y+=gravity;
        }
        else
        {
            this->position.y = -1.5;
            speed_y=0;
            speed_x=0;
        }
        this->position.y += speed_y;
        this->position.x += speed_x;
        
        
    }
}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.5 };
    return bbox;
}
