#include "PhysicsManager.h"

physicsManager::physicsManager() {
    //inicio de el mundo con la gravedad
    world = new b2World({0.0f,GRAVITY});

    // variables para la sim
    timeStep = 1.0f / TARGET_FPS;
    velocityIterations = VELOCITY_ITERATIONS;
    positionIterations = POSITION_ITERATIONS;
}

void physicsManager::Update() {
    // Avanzamos la simulación física
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2World* physicsManager::GetWorld() {
    return world;
}

physicsManager::~physicsManager() {
    delete world;
}