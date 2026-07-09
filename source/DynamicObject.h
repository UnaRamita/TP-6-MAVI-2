#pragma once
#include <box2d.h>
#include "raylib.h"
#include "Config.h"
#include "globals.h"

class DynamicObject {
private:
    b2World* world;
    b2Body* body;

    // Datos iniciales
    Vector2 position;
    Vector2 size;    // x = ancho (o radio*2), y = alto

    float angle;

    Texture2D textureBox;
    Texture2D textureProjectile;
    Color color;
    ObjectType type;

public:
    // Constructor: Solo guarda los datos
    DynamicObject(b2World* wrld, Vector2 pos, Vector2 siz, float ang);

    // Init: Crea la física según el tipo que le pidas
    void init(ObjectType type = ObjectType::CAJA);

    // Unidad 2: Aplicar el impulso para el lanzamiento
    void applyImpulse(Vector2 impulse);

    void draw();

    b2Body* GetBody() { return body; }

    ~DynamicObject();
};