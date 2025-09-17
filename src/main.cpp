#include "StateMachine.hpp"
#include "MainMenuState.hpp"
#include <memory>
#include <chrono>
extern "C" {
    #include <raylib.h>
}
int main()
{
    //tamanyo de la ventana
    const int screenWidth = 288;
    const int screenHeight = 512;
    InitWindow(screenWidth, screenHeight, "Flappy Bird");
    SetTargetFPS(60);               // EL juego corre a 60 FPS max
    
    //Implement the main loop with delta time
    std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    
    float delta_time = 0.0f;

    StateMachine state_machine = StateMachine();
    state_machine.add_state(std::make_unique<MainMenuState>(), false);
    state_machine.handle_state_changes(delta_time);
    
    

    while (!state_machine.is_game_ending() && !WindowShouldClose() )
    {
        //Usamos el delta time
        std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now(); // Tiempo actual
        delta_time = GetFrameTime();
        last_time = current_time; // Actualizamos el tiempo anterior

        state_machine.handle_state_changes(delta_time);
        state_machine.getCurrentState()->update(delta_time);

        //renderizar
        state_machine.getCurrentState()->render();       
    }

    CloseWindow();        
    return 0;
}