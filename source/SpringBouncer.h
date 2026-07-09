#pragma once
#include <box2d.h>
#include "raylib.h"
#include "Config.h"

class SpringBouncer {
private:
    // Puntero al mundo físico
    b2World* world;

    // Componentes de Box2D
    b2Body* baseBody;                 // Bloque fijo que sostiene el mecanismo
    b2Body* platformBody;             // El tabln que recibe los impactos
    b2PrismaticJoint* prismaticJoint; // El joint que actua como riel
    b2DistanceJoint* distanceJoint;   // El joint que actua como resorte

    // Propiedades guardadas en el constructor
    Vector2 position;     // Centro inicial de la plataforma (en píxeles)
    Vector2 size;         // Ancho y alto del tablón (en píxeles)
    float angleDegrees;   // Ángulo de inclinación del resorte (en grados)
    Color color;          // Color de la plataforma

    //voy a probar ponerlo aca y que directamente se ejecute cuando lo creas, si no es buena practica y recibe alguna correcion lo cambio 
    void init();

public:
    // El constructor solo guarda los parámetros en las variables privadas y llama a init()
    SpringBouncer(b2World* wrld, Vector2 pos, Vector2 size, float angleDegrees, Color col = MAROON);

    void draw();

    ~SpringBouncer();
};