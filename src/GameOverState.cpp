#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "StateMachine.hpp"   // IMPORTANTE
#include <memory>

void GameOverState::handleInput() {
    if (IsKeyPressed(KEY_SPACE)) { //si perdemos y pulsamos espacio, volvemos al menu principal
        this->state_machine->add_state(std::make_unique<MainMenuState>(), true);
    }
}

void GameOverState::update(float deltaTime) {
    handleInput();
}

void GameOverState::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    
    DrawText(TextFormat("GAME OVER"), GetScreenWidth()/2 - MeasureText("GAME OVER", 40)/2,
        GetScreenHeight()/2 - 20, 40, RED);

    DrawText(TextFormat("Puntuacion: %d", finalScore), // se recibe la puntuación final desde el constructor
        GetScreenWidth()/2 - MeasureText(TextFormat("Puntuacion: %d", finalScore), 20)/2,
        GetScreenHeight()/2 + 30, 20, DARKGRAY);

    DrawText("Presiona ESPACIO para reiniciar", 30,
        GetScreenHeight()/2 + 70, 20, DARKGRAY);

    EndDrawing();
}
