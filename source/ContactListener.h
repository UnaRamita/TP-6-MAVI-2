#pragma once
#include <box2d.h>
#include "globals.h" 
class contactListener : public b2ContactListener
{
public:
	contactListener(int* score, GameState* gameState);

	void BeginContact(b2Contact* contact) override; // OJO: la B mayúscula, es BeginContact en Box2D

private:
	int* scoreRef; //puntero a score para poder modificarlo desde el listener
	GameState* gameStateRef; //puntero a gameState para poder modificarlo desde el listener
};
