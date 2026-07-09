#include "SpringBouncer.h"
#include <cmath>

SpringBouncer::SpringBouncer(b2World* wrld, Vector2 pos, Vector2 siz, float angDeg, Color col)
    : world(wrld), position(pos), size(siz), angleDegrees(angDeg), color(col),
    baseBody(nullptr), platformBody(nullptr), prismaticJoint(nullptr), distanceJoint(nullptr) {
    init();
}

//inicializacion y calculos del resorte
void SpringBouncer::init() {
    // angulo en radianes
    float angleRad = angleDegrees * DEG2RAD;
    // calculo del eje de movimiento usando Seno y Coseno (para el riel y que el resorte solo se mueva en la direccion requerida)
    b2Vec2 axis(sinf(angleRad), -cosf(angleRad));

    // posicion inicial en metros
    b2Vec2 platformPosMetros(position.x / SCALE, position.y / SCALE);

	// calculo de la posicion de la base fija, desplazada 60 píxeles en la dirección opuesta al movimiento para que el resorte tenga espacio para estirarse
    float offsetMetros = 60.0f / SCALE;
    b2Vec2 basePosMetros = platformPosMetros - (offsetMetros * axis);

	//creacion de la base fija (cuerpo estatico)
    b2BodyDef baseDef;
    baseDef.type = b2_staticBody;
    baseDef.position.Set(basePosMetros.x, basePosMetros.y);
    baseBody = world->CreateBody(&baseDef);//PONER EN EL FONDO

	//forma de la base, un cuadrado de 10x10 pixeles
    b2PolygonShape baseShape;
    baseShape.SetAsBox((10.0f / 2.0f) / SCALE, (10.0f / 2.0f) / SCALE);
    baseBody->CreateFixture(&baseShape, 0.0f); // Densidad 0 porque es estatico


    //Plataforma que va en el extremo del resorte
    b2BodyDef platDef;
    platDef.type = b2_dynamicBody;
    platDef.position.Set(platformPosMetros.x, platformPosMetros.y);
    platDef.angle = angleRad; // Le aplicamos la rotación inicial al cuerpo
	platformBody = world->CreateBody(&platDef);//PONER EN EL FONDO

    // forma del tablon usando las medidas pasadas por parámetro
    b2PolygonShape platShape;
    platShape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &platShape;
    fixtureDef.density = 2.0f;       // masa
    fixtureDef.friction = 0.6f;      // friccion
	fixtureDef.restitution = 0.1f;   // rebote de la superficie (aca no queremos que rebote mucho)
	platformBody->CreateFixture(&fixtureDef);//poner en el fondo


	// guia/riel para que el resorte solo se mueva en la direccion del eje calculado
    b2PrismaticJointDef prismaticDef;

	// conexion de la base fija con la plataforma usando el eje calculado para limitar su movimiento a esa direccion
    prismaticDef.Initialize(baseBody, platformBody, platformPosMetros, axis);

    //limites del resorte
    prismaticDef.enableLimit = true;
    prismaticDef.lowerTranslation = -60.0f / SCALE; // minimo
    prismaticDef.upperTranslation = 20.0f / SCALE;  // maximo

	// guardado del joint en el miembro de la clase para poder acceder a sus propiedades luego
    prismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&prismaticDef);


    //resorte
    b2DistanceJointDef distanceDef;

    // Conectamos los centros de ambos cuerpos
    distanceDef.Initialize(baseBody, platformBody, basePosMetros, platformPosMetros);

    //esto lo puse despues por que no estaba funcionando y era por esto asi que IMPORTANTE
    distanceDef.minLength = 0.0f;          //dejo que se comprima hasta el fondo
    distanceDef.maxLength = 1000.0f;       //dejo que se estire mucho, el limite en realidad lo pone prismaticjoint justo arriba de esto

    // comportaiento elastico del resorte
    float frequencyHz = 1.0f;   // Dureza
    float dampingRatio = 0.1f;  // Freno del rebote

	// fuerza del resorte calculada por Box2D a partir de la frecuencia y el damping
    b2LinearStiffness(distanceDef.stiffness,distanceDef.damping, frequencyHz, dampingRatio, baseBody,platformBody);

    // Guardamos el joint en nuestra variable miembro
    distanceJoint = (b2DistanceJoint*)world->CreateJoint(&distanceDef);
}

void SpringBouncer::draw() {

    // posiciones actuales
    b2Vec2 bPos = baseBody->GetPosition();
    b2Vec2 pPos = platformBody->GetPosition();

    // resorte
    DrawLineV({ bPos.x * SCALE, bPos.y * SCALE }, { pPos.x * SCALE, pPos.y * SCALE }, RED);
	// anclaje del resorte
    DrawCircle(bPos.x * SCALE, bPos.y * SCALE, 5.0f, RED);

    // plataforma
    float angDeg = platformBody->GetAngle() * RAD2DEG;
    DrawRectanglePro({ pPos.x * SCALE, pPos.y * SCALE, size.x, size.y },{ size.x / 2.0f, size.y / 2.0f }, angDeg, color);
}


SpringBouncer::~SpringBouncer() {
}