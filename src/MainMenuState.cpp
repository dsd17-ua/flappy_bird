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

    spawnTimer += deltaTime; // Actualizamos el temporizador de spawn
    if (spawnTimer >= SPAWN_EVERY) { //si ha pasado el tiempo suficiente, generamos un nuevo par de tuberías
        spawnTimer = 0.0f;

        int offsetTop = GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2);

        PipePair newPipe;
        newPipe.top = { (float)GetScreenWidth(), (float)-offsetTop, PIPE_W, PIPE_H };
        newPipe.bot = { (float)GetScreenWidth(), (float)(PIPE_H - offsetTop + PIPE_GAP), PIPE_W, PIPE_H };
        
        pipes.push_back(newPipe);
    }

    // --- Mover tuberías existentes ---
    for (auto& pipe : pipes) {
        pipe.top.x -= PIPE_SPEED * deltaTime;
        pipe.bot.x -= PIPE_SPEED * deltaTime;
    }

    // --- Eliminar tuberías que salieron de pantalla ---
    while (!pipes.empty() && pipes.front().top.x + PIPE_W < 0) {
        pipes.pop_front();
    }
}

void MainMenuState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Bienvenido a Flappy Bird DCA", 10, 200, 20, DARKGRAY); 

    //DIBUJAMOS EL PAJARO
    DrawCircle((int)bird.x, (int)bird.y, RADIO_PAJARO, RED);

    // --- render de pipes ---
    for (const auto& pipe : pipes) {
        DrawRectangle((int)pipe.top.x, (int)pipe.top.y, (int)pipe.top.width, (int)pipe.top.height, GREEN);
        DrawRectangle((int)pipe.bot.x, (int)pipe.bot.y, (int)pipe.bot.width, (int)pipe.bot.height, GREEN);
    }

 
    EndDrawing();
}