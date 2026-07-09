#include "DynamicObject.h"

DynamicObject::DynamicObject(b2World* wrld, Vector2 pos, Vector2 siz, float ang)
    : world(wrld), position(pos), size(siz), angle(ang), body(nullptr), type(ObjectType::CAJA) {
    textureBox = { 0 };
	textureProjectile = { 0 };
}

void DynamicObject::init(ObjectType typ) {
    type = typ;

    // definicion del cuerpo (Cuerpo Dinámico)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    // paso a metros usando sclae
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.angle = angle;
    

    // definicion de la forma y fixture
    b2FixtureDef fixtureDef;

    //punteros para las formas
    b2PolygonShape boxShape;
    b2CircleShape circleShape;

    if (type == ObjectType::CAJA) {
        boxShape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);
        fixtureDef.shape = &boxShape;
		textureBox = LoadTexture("assets/box.png");
    }
    else if (type == ObjectType::PROYECTIL) {
        // En el caso del circulo, uso size.x como el diametro
        circleShape.m_radius = (size.x / 2.0f) / SCALE;
        fixtureDef.shape = &circleShape;
		textureProjectile = LoadTexture("assets/canonBall.png");
    }

    // propiedades fisicas
    fixtureDef.density = PROYECTILE_DENSITY;     // masa basicamente
    fixtureDef.friction = PROYECTILE_FRICTION;   // resistencia al deslizamiento
    fixtureDef.restitution = PROYECTILE_BOUNCINESS; // rebote
    //aplicamos todo
    body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
	body->GetUserData().pointer = static_cast<uintptr_t>(type); //asigno el tipo a userData para poder identificarlo en el contactListener
}

void DynamicObject::applyImpulse(Vector2 impulse) {
    // impulsos producen un cambio inmediato en la velocidad como si fuece un salto o un golpe
    if (body) {
        body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
    }
}

void DynamicObject::draw() {
    
    b2Vec2 pos = body->GetPosition();
    float ang = body->GetAngle() * RAD2DEG;
    
    if (type == ObjectType::CAJA) {
        //dibujo cada de municion
		DrawTexturePro(textureBox, { 0.0f, 0.0f, (float)textureBox.width, (float)textureBox.height }, { pos.x * SCALE, pos.y * SCALE, size.x, size.y }, { size.x / 2.0f, size.y / 2.0f }, ang, WHITE);
    }
    else if (type == ObjectType::PROYECTIL) {
        //dibujo bala de cañon
		DrawTexturePro(textureProjectile, { 0.0f, 0.0f, (float)textureProjectile.width, (float)textureProjectile.height }, { pos.x * SCALE, pos.y * SCALE, size.x, size.y }, { size.x / 2.0f, size.y / 2.0f }, ang, WHITE);
    }
}

DynamicObject::~DynamicObject() {
    if (type == ObjectType::PROYECTIL) {
        UnloadTexture(textureProjectile);
    }
	else if (type == ObjectType::CAJA){
        UnloadTexture(textureBox);
	}
    if (body) world->DestroyBody(body);
}