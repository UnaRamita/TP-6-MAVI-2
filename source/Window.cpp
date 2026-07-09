#include "Window.h"

void Window::Initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
}

void Window::Close() {
    CloseWindow();
}
