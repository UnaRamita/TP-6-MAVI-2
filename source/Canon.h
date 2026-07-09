#pragma once
#include "raylib.h"
#include <cmath>
#include "Config.h"

class Preview {
private:
    Vector2 position;

    float angle;      // En grados
    float lineLength;

    int dotsCount;

	Texture2D textureCanon;
public:
    Preview(Vector2 pos);

    // Controles de ángulo
    void Rotate(float amount);
    float GetAngle() const { return angle; } // Getter para el lanzamiento físico
    Vector2 GetPosition() const { return position; }

    void Draw();
    ~Preview();
};