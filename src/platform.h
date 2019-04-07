#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H


class Platform {
public:
    Platform() {}
    Platform(float x,float y, float opp_x,float opp_y,color_t color);
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif 
