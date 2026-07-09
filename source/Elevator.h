#pragma once
#include < box2d.h>
#include "raylib.h"
#include "Config.h"

class Elevator {
private:
    b2World* world;
    b2Body* baseBody;
    b2Body* platformBody;
    b2PrismaticJoint* joint;

    float speed;
    Vector2 size;

public:
    Elevator(b2World* wrld, Vector2 pos, Vector2 size);
    void update(int moveUp); // Activación por input
    void draw();
};