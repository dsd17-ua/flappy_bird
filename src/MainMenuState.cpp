#include "MainMenuState.hpp"
#include <iostream>

MainMenuState::MainMenuState()
{
}

void MainMenuState::init()
{
    std::cout << "You are in the Main Menu State" << std::endl;

    //Iniciamos el pajaro
    this->bird.x=200.0f;
    this->bird.y=200.0f;
    this->bird.vy=0.0f; // El pajaro empieza sin velocidad
}

void MainMenuState::handleInput()
{ 
    if(IsKeyPressed(KEY_SPACE)){
        bird.vy=-300.0f; // impulso hacia arriba. Valor negativo porque el origen (0,0) está en la esquina superior izquierda
    }
}

void MainMenuState::update(float deltaTime)
{
    this->handleInput();

    //actualizamos gravedad
    bird.vy += GRAVEDAD * deltaTime; // Incrementamos la velocidad vertical debido a la gravedad
    
    //posicion del pajaro
    bird.y += bird.vy * deltaTime; // Actualizamos la posición vertical del pájaro
    // limitar dentro de la ventana
    if (bird.y < 0) {
        bird.y = 0;
        bird.vy = 0;
    }
    if (bird.y > 512 - RADIO_PAJARO) { // 512 = altura ventana
        bird.y = 512 - RADIO_PAJARO;
        bird.vy = 0;
    }
}

void MainMenuState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Bienvenido a Flappy Bird DCA", 10, 200, 20, DARKGRAY); 

    //DIBUJAMOS EL PAJARO
    DrawCircle((int)bird.x, (int)bird.y, RADIO_PAJARO, RED);
 
    EndDrawing();
}