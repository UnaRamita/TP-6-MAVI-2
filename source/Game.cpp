#include "Game.h"
Game::Game() : physics(nullptr)
{
	ground = nullptr;
	wallLeft = nullptr;
	wallRight = nullptr;
	wallElevator = nullptr;
	Background = {0};

	amunition = 1;

}

void Game::inits() {
	Background = LoadTexture("assets/background_glacial_mountains.png");
	//iniciamos el mundo fisico
	physics = new physicsManager();

	b2World* world = physics->GetWorld();
	//colisiones
	contactL = new contactListener(&score, &gameState);
	world->SetContactListener(contactL);
	//iniciamos los objetos estaticos
	// Piso
	ground = new staticObjects(world, { (float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 20.0f }, { (float)SCREEN_WIDTH, 40.0f });
	ground->init();

	// Pared Izquierda
	wallLeft = new staticObjects(world, { 10.0f, (float)SCREEN_HEIGHT / 2.0f }, { 20.0f, (float)SCREEN_HEIGHT });
	wallLeft->init();

	// Pared Derecha
	wallRight = new staticObjects(world, { (float)SCREEN_WIDTH - 10.0f, (float)SCREEN_HEIGHT / 2.0f }, { 20.0f, (float)SCREEN_HEIGHT });
	wallRight->init();
	//pared para que no se salga la caja
	wallElevator = new staticObjects(world, { 625.0f, 350.0f }, { 20.0f, 600.0f });
	wallElevator->init();

	//los pongo en la lista para dibujarlos dsp
	environment.push_back(ground);
	environment.push_back(wallLeft);
	environment.push_back(wallRight);
	environment.push_back(wallElevator);	
	//pared objetivo
	targetBody = new staticObjects(world, { 600.0f, 150.0f }, { 30.0f, 60.0f });
	targetBody->init(ObjectType::OBJETIVO);
	environment.push_back(targetBody);
	//elevador
	elevator = new Elevator(world, { 700.0f, 550.0f }, { 100.0f, 20.0f });
	//cajas
	box = new DynamicObject(world, { 700.0f, 400.0f }, { 40.0f, 40.0f }, 0.0f);
	box->init(ObjectType::CAJA);
	//resorte
	bouncer = new SpringBouncer(world, { 700.0f, 300.0f }, { 80.0f, 20.0f }, 180.0f,BLUE);
	//canon
	canon = new Preview({ 100.0f, (float)SCREEN_HEIGHT - 60.0f });
}

void Game::inputs() {
	if (InputManager::R()) {
		// Reiniciar el juego
		score = 0;
		amunition = 1;
		gameState = GameState::PLAYING;
		boxInZone = false;
		projectiles.clear();
		scoredProjectiles.clear();
		delete physics; // Limpiar el mundo físico actual
		inits(); // Re-inicializar todo
		return; // Salir para evitar procesar más inputs en este frame
	}
	//esta es la parte que agregue para este tp aca
	if (gameState == GameState::FINISHED) { return; } // si se gano no entran mas inputs
	//
	if (InputManager::P()) {
		if (gameState == GameState::PLAYING) {
			gameState = GameState::PAUSE;
		}
		else if (gameState == GameState::PAUSE) {
			gameState = GameState::PLAYING;
		}
	}
	if (gameState == GameState::PAUSE) { return; }
	//
	if (gameState == GameState::PLAYING) {
		bool elevatorM = false;
		if (InputManager::Space() && amunition > 0) {
			amunition--;
			// Paso el angulo del canñon
			float angleInRad = canon->GetAngle() * DEG2RAD;
			//para el size en vez de pasar el radio, paso el diametro (radio*2)
			float diameter = (PROYECTILE_RADIUS * SCALE) * 2.0f;

			DynamicObject* projectile = new DynamicObject(physics->GetWorld(), canon->GetPosition(), { diameter,diameter }, angleInRad);
			//le digo que es un circulo
			projectile->init(ObjectType::PROYECTIL);

			//aca ya esta creado el proyectil y le aplico el impulso para lanzarlo, dsp lo dibujo en el draw
			float launchPower = 15.0f; //si quisiera poner algun input para variar la potencia del lanzamiento, pondria esto en otro lado
			//creo el vector para el impulso, con coseno y seno para que sea en la direccion de la preview
			Vector2 impulse = { cosf(angleInRad) * launchPower, sinf(angleInRad) * launchPower };
			//aplico el impulso al proyectil
			projectile->applyImpulse(impulse);
			//lo agrego a la lista de proyectiles para dibujarlo dsp
			projectiles.push_back(projectile);

		}
		if (InputManager::Down()) {
			elevator->update(1); elevatorM = true;
		}
		else if (InputManager::Up()) {
			elevator->update(2); elevatorM = true;
		}
		if (InputManager::A()) {
			canon->Rotate(-1);
		}
		else if (InputManager::D()) {
			canon->Rotate(1);
		}
		if (!elevatorM) elevator->update(0); // Si no se presiona W ni S
	}
}
void Game::collider() {
	Rectangle rechargeZone = { 650.0f, 275.0f, 100.0f, 50.0f }; 
	
	// Obtenemos la posición actual del cubo en píxeles
	b2Vec2 boxPosFeet = box->GetBody()->GetPosition();
	Vector2 boxPosPixels = { boxPosFeet.x * SCALE, boxPosFeet.y * SCALE };

	// Como Box2D tiene el origen en el CENTRO, para Raylib le restamos la mitad del ancho/alto (40 / 2 = 20)
	Rectangle boxRect = {boxPosPixels.x - 20.0f, boxPosPixels.y - 20.0f,40.0f, 40.0f };
	
	// CheckCollisionPointRec comprueba si el centro del cubo entró al rectángulo de la zona
	if (CheckCollisionRecs(boxRect, rechargeZone)) {
		if (!boxInZone) {
			amunition++;      // Suma 1 bala
			boxInZone = true; // Bloquea para que no sume 
		}
	}
	else {
		boxInZone = false;    // Cuando se separan, se libera 
	}
}

void Game::load() {
	//fondo
	DrawTexture(Background, 0, 0, WHITE);
	//actualizamos la fisica
	if (gameState == GameState::PLAYING) {
		physics->Update();
	}
	//inputs
	inputs();
	//draws texts
	DrawText("Use W and S to move the elevator, A and D to rotate the canon direction", 20, 5, 18, BLACK);
	DrawText("R to restart the game, P to pause", 20, 20, 18, BLACK);

	DrawText(TextFormat("Puntaje: %d / 5", score), 20, 40, 22, BLACK);
	DrawText(TextFormat("Balas: %d", amunition), 20, 70, 22, BLACK);
	if (gameState == GameState::FINISHED) {
        DrawText("¡GANASTE!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, GREEN);
    }
	if (gameState == GameState::PAUSE) {
		DrawText("PAUSA", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 20, 40, YELLOW);
	}

	//statics
	for (auto obj : environment) obj->draw();
	//projectiles
	canon->Draw();
	for (auto proj : projectiles) proj->draw();
	//elevador
	elevator->draw();
	//cajas
	box->draw();
	//resorte
	bouncer->draw();
	//collision detect
	collider();
}

void Game::run() {

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		load();

		EndDrawing();
	}

}
Game::~Game()
{
}