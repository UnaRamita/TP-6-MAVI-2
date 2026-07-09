#pragma once
#include "raylib.h"
#include "config.h"

class Window {
public:
    // Inicializa la ventana y el audio si fuera necesario
    static void Initialize();

    // Cierra la ventana y libera recursos
    static void Close();

};