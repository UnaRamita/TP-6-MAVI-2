#pragma once
#include "raylib.h"

class InputManager {
public:
    // Detecta si se presionó la tecla para lanzar (Unidad 2)
    static bool SpacePressed();

    // Podés agregar otros métodos para rotación o reset
    static bool Down();
    static bool Up();
    static bool Space();
    static bool A();
    static bool D();
    static bool R();
	static bool P();
};