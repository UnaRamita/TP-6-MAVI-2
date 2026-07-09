#include "Canon.h"

Preview::Preview(Vector2 pos) {
    position = pos;
    angle = -45.0f;    //  apuntando hacia arriba a la derecha
    lineLength = 100.0f; // Largo de la "mira"
    dotsCount = 10;      // Cantidad de puntitos
	textureCanon = LoadTexture("assets/canon.png");
}

void Preview::Rotate(float amount) {
    angle += amount;
}

void Preview::Draw() {
    // proyectil preview
    // uso el radio definido en Config para que coincida con el real
    DrawCircle(position.x, position.y, (PROYECTILE_RADIUS * SCALE), GRAY);

    //dibujo de la línea punteada (la dirección)
    // convertimos el angulo a radianes para usar cos y sin
    float angleRad = angle * DEG2RAD;

    for (int i = 1; i <= dotsCount; i++) {
        //posición de cada punto
        float dist = (lineLength / dotsCount) * i;
        float dotX = position.x + cosf(angleRad) * dist;
        float dotY = position.y + sinf(angleRad) * dist;

        // dibujamos
        DrawCircle(dotX, dotY, 2.0f, MAROON);
    }
    // ancho y alto del cañon
    float drawWidth = (float)textureCanon.width * 2.4f;
    float drawHeight = (float)textureCanon.height * 2.4f;

    // posicion de donde se dibuja el cañon
    Rectangle destRec = { position.x, position.y, drawWidth, drawHeight };

    // origen osea el punto de rotacion
    Vector2 origin = { drawWidth / 4.0f, drawHeight / 2.0f };

    //draw
    DrawTexturePro(textureCanon, { 0.0f, 0.0f, (float)textureCanon.width, (float)textureCanon.height },destRec, origin,angle, WHITE);
}

Preview::~Preview() {}