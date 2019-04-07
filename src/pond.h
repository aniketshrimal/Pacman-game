#include "main.h"

#ifndef POND_H
#define POND_H


class Pond {
public:
    Pond() {}
    Pond(float x, float y,float r,color_t color);
    glm::vec3 position;
    float radius;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Pond_H
