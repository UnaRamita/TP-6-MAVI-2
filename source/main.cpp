#include "Window.h"
#include "Game.h"

int main() {
    Window::Initialize();

    Game game;
    game.inits();
    game.run();

    Window::Close();
    return 0;
}