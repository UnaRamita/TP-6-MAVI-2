#pragma once

// --- Configuración de Ventana ---
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
static const char* WINDOW_TITLE = "MAVI - TP Unidad 4";
const int TARGET_FPS = 60;

// Box2D
// Factor de conver: 1 metro = 30 píxeles
const float SCALE = 30.0f; //esto no se bien si lo uso, cuando escriba lo demas chequeo

// Configuración de Juego
const float GRAVITY = 9.8f; // Gravedad en m/s^2
const float PROYECTILE_RADIUS = 0.5f; // En metros (Box2D)
const float PROYECTILE_DENSITY = 1.0f; // Densidad del proyectil
const float PROYECTILE_FRICTION = 0.3f; // Fricción del proyectil
const float PROYECTILE_BOUNCINESS = 1.0f; // Rebote del proyectil
// Configuración de Simulacion
const int VELOCITY_ITERATIONS = 8; // Para calculo de velocidad
const int POSITION_ITERATIONS = 3; // Para calculo de posición