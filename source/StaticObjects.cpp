#include "StaticObjects.h"
staticObjects::staticObjects(b2World* wrld, Vector2 pos, Vector2 size)
{
	body = nullptr;
	world = wrld;
	objSize = size;
	objPos = pos;
	type = ObjectType::NULO;
	texture = { 0 };
}

void staticObjects::init(ObjectType tipo) {
	type = tipo;
	//definicion del cuerpo (estatico en este caso)
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(objPos.x / SCALE, objPos.y / SCALE);

	//forma y propiedades 
	//forma
	b2PolygonShape groundBox;
	groundBox.SetAsBox((objSize.x / 2.0f) / SCALE, (objSize.y / 2.0f) / SCALE);
	//propiedades
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.friction = 0.5f;     // algo de friccion
	fixtureDef.restitution = 0.2f;  // rebote

	//aplicamos todo
	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	//guardamos etiqueta 
	body->GetUserData().pointer = static_cast<uintptr_t>(tipo);
	if(type == ObjectType::OBJETIVO) {
		texture = LoadTexture("assets/target.png");
	}
}

void staticObjects::draw() {
	// posicion box2d
	b2Vec2 pos = body->GetPosition();

	// no se si va el scale o no aca si no se ve bien es aca
	float drawX = objPos.x;
	float drawY = objPos.y;

	if (type == ObjectType::OBJETIVO) {

		//parte de la imagen en particular aca toda
		Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

		// tamaño
		Rectangle destRec = { drawX, drawY, objSize.x, objSize.y };

		//punto de origen
		Vector2 origin = { objSize.x / 2.0f, objSize.y / 2.0f };

		// draww
		DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
	}
	else if (type == ObjectType::ESCENARIO) {
		//primer llave es el rectangle, segunda llave es el origen de donde se dibuja
		DrawRectanglePro({ drawX, drawY, objSize.x, objSize.y }, { objSize.x / 2.0f, objSize.y / 2.0f }, 0.0f, DARKGRAY);
	}
	
}
															
staticObjects::~staticObjects()
{
	if (body && world) {
		world->DestroyBody(body);
	}
	if (type == ObjectType::OBJETIVO) {
		UnloadTexture(texture);
	}
}