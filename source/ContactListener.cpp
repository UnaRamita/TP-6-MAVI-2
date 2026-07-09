#include "ContactListener.h"
#include "globals.h" // Asegurate de que acá esté tu enum ObjectType
#include <iostream>

contactListener::contactListener(int* score, GameState* gameState)
    : scoreRef(score), gameStateRef(gameState) {
}

void contactListener::BeginContact(b2Contact* contact) {
	//objetos que colisionan
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// puntero de user data de cada cuerpo
    uintptr_t dataA = bodyA->GetUserData().pointer;
    uintptr_t dataB = bodyB->GetUserData().pointer;

	// los transformamos a ObjectType para poder compararlos ///// aca le estaba errando antes jeje(recordar)
    ObjectType typeA = static_cast<ObjectType>(dataA);
    ObjectType typeB = static_cast<ObjectType>(dataB);

	// evaluamos si uno es proyectil y el otro es objetivo
    bool condicion1 = (typeA == ObjectType::PROYECTIL && typeB == ObjectType::OBJETIVO);
    bool condicion2 = (typeA == ObjectType::OBJETIVO && typeB == ObjectType::PROYECTIL);

    if (condicion1 || condicion2) {
        if (scoreRef && gameStateRef && *gameStateRef == GameState::PLAYING) {
            (*scoreRef)++;
            std::cout << "[FÍSICA] ¡Impacto certero detectado! Score: " << *scoreRef << std::endl; //texto de control (?

            // Conseguimos cuál de los dos cuerpos es el proyectil para anularlo
            b2Body* projectileBody = (typeA == ObjectType::PROYECTIL) ? bodyA : bodyB;

			// cambio de tipo a nulo para que no sume más puntos si sigue en contacto con el objetivo
            projectileBody->GetUserData().pointer = static_cast<uintptr_t>(ObjectType::NULO);

            // Condición de victoria
            if (*scoreRef >= 5) {
                *gameStateRef = GameState::FINISHED;
            }
        }
    }
}