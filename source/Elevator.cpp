#include "Elevator.h"

Elevator::Elevator(b2World* wrld, Vector2 pos, Vector2 siz) : world(wrld), size(siz), speed(5.0f) {
    // Base estatica
    b2BodyDef bDef;
    bDef.position.Set(pos.x / SCALE, pos.y / SCALE);
    baseBody = world->CreateBody(&bDef);

    // Plataforma movil
    b2BodyDef pDef;
    pDef.type = b2_dynamicBody;
    pDef.position.Set(pos.x / SCALE, (pos.y - 100.0f) / SCALE);
    platformBody = world->CreateBody(&pDef);

    b2PolygonShape shape;
    shape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);
    platformBody->CreateFixture(&shape, 1.0f);

    // 3. Prismatic Joint El Riel
    b2PrismaticJointDef jDef;
    b2Vec2 axis(0.0f, 1.0f); // Movimiento vertical
    jDef.Initialize(baseBody, platformBody, platformBody->GetPosition(), axis);

    jDef.enableLimit = true;
    jDef.lowerTranslation = -5.0f / SCALE; // Límite superior
    jDef.upperTranslation = 100.0f / SCALE; // Límite inferior

    // ACTIVAR MOTOR
    jDef.enableMotor = true;
    jDef.maxMotorForce = 1000.0f; // Fuerza del ascensor
    jDef.motorSpeed = 0.0f;      // Inicia quieto

    joint = (b2PrismaticJoint*)world->CreateJoint(&jDef);

}

void Elevator::update(int moveUp) {
    // Si moveUp es true, motorSpeed es negativo (sube), sino positivo (baja)
	if (moveUp == 1){
        joint->SetMotorSpeed(-speed);
    }
    else if (moveUp == 2){
        joint->SetMotorSpeed(speed);
    }
    else if(moveUp == 0) {
        joint->SetMotorSpeed(0.0f); // Detener el motor si no se presiona ninguna tecla
	}
}

void Elevator::draw() {
    b2Vec2 pos = platformBody->GetPosition();
    DrawRectangle(pos.x * SCALE - size.x / 2, pos.y * SCALE - size.y / 2, size.x, size.y, BLUE);
}