#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_x;
    double speed_y;
    double gravity;
    double deaccn;
    int score;
    int level;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Player_H
