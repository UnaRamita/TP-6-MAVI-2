#pragma once
#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include "Config.h"
#include "globals.h"

class staticObjects
{
public:
	staticObjects(b2World* world, Vector2 pos, Vector2 size);

	b2Body* GetBody() { return body; }

	void init(ObjectType tipo = ObjectType::ESCENARIO); //si no pongo nada el predet es escenario, dsp lo uso para el target que es un tipo distintop
	void draw();
	~staticObjects();

private:
	b2Body* body;
	b2World* world;
	ObjectType type;

	Texture2D texture;

	Vector2 objSize;
	Vector2 objPos;
};

