#pragma once
#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include "Config.h"

class physicsManager {
private:
    b2World* world;

    // variables para el step
    float timeStep;
    int velocityIterations;
    int positionIterations;

public:
    // El constructor ahora puede tomar la gravedad de Config por defecto
    physicsManager();
    ~physicsManager();

    void Update();
    b2World* GetWorld();
};