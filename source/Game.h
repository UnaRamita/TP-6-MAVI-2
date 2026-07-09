#pragma once
#ifndef NDEBUG
#include <vld.h>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "PhysicsManager.h"
#include "StaticObjects.h"
#include "Config.h"
#include "Input.h"
#include "Elevator.h"
#include "DynamicObject.h"
#include "SpringBouncer.h"
#include "Canon.h"
#include "ContactListener.h"
#include "globals.h"
class Game
{
public:
	Game();
	~Game();

	void inits();

	void run();

private:
	int score = 0;
	int amunition;

	GameState gameState = GameState::PLAYING; // Estado del juego
	bool boxInZone = false; // Para controlar la recarga de balas

	Texture2D Background;

	staticObjects* ground;
	staticObjects* wallLeft;
	staticObjects* wallRight;
	staticObjects* wallElevator;
	staticObjects* targetBody;

	void collider();

	Preview* canon;

	contactListener* contactL;

	DynamicObject* box;
	DynamicObject* box2;
	Elevator* elevator;
	SpringBouncer* bouncer;

	void load();
	void inputs();

	physicsManager* physics;
	std::vector<staticObjects*> environment;//ambiente, suelo y paredes
	std::vector<DynamicObject*> projectiles; // Lista para almacenar los proyectiles lanzados
	std::vector<DynamicObject*> scoredProjectiles;
};
