#include "main.h"

#ifndef PLANK_H
#define PLANK_H


class Plank {
public:
    Plank() {}
    Plank(float x, float y,float r,color_t color);
    glm::vec3 position;
    glm::vec3 point;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    color_t colour;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};

#endif // Plank_H
