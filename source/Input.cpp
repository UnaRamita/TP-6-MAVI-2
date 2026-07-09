#include "Input.h"
// la idea de esto es si despues quiero poner otras teclas o manejar por ejemplo tiempo precionado o algo asi hacerlo desde aca aunque ahora mismo es mas o menos lo mismo que manejarlo directamente en el game
bool InputManager::SpacePressed() {
    return IsKeyPressed(KEY_SPACE);
}
// veo si los ocupo para la direccion del lanzamiento aunque no lo pide la consigna
bool InputManager::Down() {
    return IsKeyDown(KEY_W);
}

bool InputManager::Up() {
    return IsKeyDown(KEY_S);
}
bool InputManager::Space() {
    return IsKeyPressed(KEY_SPACE);
}
bool InputManager::A() {
    return IsKeyDown(KEY_A);
}
bool InputManager::D() {
    return IsKeyDown(KEY_D);
}  
bool InputManager::R() {
    return IsKeyPressed(KEY_R);
}
bool InputManager::P() {
	return IsKeyPressed(KEY_P);
}
