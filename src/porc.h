#include "main.h"

#ifndef PORC_H
#define PORC_H


class Porc {
public:
    Porc() {}
    Porc(float x, float y,float h,float l,color_t color);
    glm::vec3 position;
    float rotation;
    float height ;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speed;
    bounding_box_porc bounding_box();
private:
    VAO *object;
};

#endif // Porc_H
