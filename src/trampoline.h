#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y,float h,float l,color_t color);
    glm::vec3 position;
    float height;
    float length;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_tramp bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // Trampoline_H
