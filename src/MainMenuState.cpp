#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
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

    // cargar sprite del pájaro
    birdSprite = LoadTexture("assets/yellowbird-midflap.png");
    bird.width = birdSprite.width;
    bird.height = birdSprite.height;

    // cargar sprite de tuberías
    pipeSprite = LoadTexture("assets/pipe-green.png");
    PIPE_W = pipeSprite.width;
    PIPE_H = pipeSprite.height;

    // definir gap como altura del pájaro * 4.5
    PIPE_GAP = bird.height * 4.5f;

}

void MainMenuState::handleInput()
{ 
    if(IsKeyPressed(KEY_SPACE)){
        bird.vy=-250.0f; // impulso hacia arriba. Valor negativo porque el origen (0,0) está en la esquina superior izquierda
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
        pipe.top.x -= PIPE_SPEED * deltaTime; // Mover tubería superior
        pipe.bot.x -= PIPE_SPEED * deltaTime; // Mover tubería inferior


        //una vez que el pájaro ha pasado la tubería, sumamos un punto
        if (!pipe.scored && pipe.top.x + PIPE_W < bird.x - RADIO_PAJARO) { //pipe.scored es para que solo sume un punto por tubería
            score++;
            pipe.scored = true;
            std::cout << "Sumando punto! Score: " << score << std::endl;
        }
        
    }

    // --- Eliminar tuberías que salieron de pantalla ---
    while (!pipes.empty() && pipes.front().top.x + PIPE_W < 0) {
        pipes.pop_front();
    }

    // --- Bounding box del pájaro ---
    Rectangle playerBox = {
        bird.x,
        bird.y,
        (float)bird.width,
        (float)bird.height
    };


    //COLISIONES CON TUBERIAS
    for (const auto& pipe : pipes) {
        if (CheckCollisionRecs(playerBox, pipe.top) || // comprobamos colisión con cada tubería
            CheckCollisionRecs(playerBox, pipe.bot)) {
                std::cout << "Colisión detectada!" << std::endl;

            this->state_machine->add_state(std::make_unique<GameOverState>(score), true); //si se produce colisión, vamos al estado de Game Over
            return; // salimos del update para no seguir
        }
    }

    //COLISION CON LIMITES DE LA VENTANA
    if (bird.y - RADIO_PAJARO < 0 || bird.y + RADIO_PAJARO > GetScreenHeight()) {
        this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
        return;
    }


}

        

void MainMenuState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // --- Dibujar el pájaro con sprite ---
    DrawTexture(birdSprite, (int)bird.x, (int)bird.y, WHITE);

    // --- Dibujar tuberías ---
    for (const auto& pipe : pipes) {
        // tubería superior (rotada 180 grados)
        DrawTextureEx(pipeSprite, {pipe.top.x + PIPE_W, pipe.top.y + PIPE_H}, 180.f, 1.0f, WHITE);

        // tubería inferior
        DrawTextureEx(pipeSprite, {pipe.bot.x, pipe.bot.y}, 0.f, 1.0f, WHITE);
    }

    // --- Dibujar puntuación ---
    std::string scoreText = std::to_string(score);
    DrawText(scoreText.c_str(), 10, 10, 30, BLACK);

    EndDrawing();
}

//destructor
MainMenuState::~MainMenuState()
{
    UnloadTexture(birdSprite);
    UnloadTexture(pipeSprite);

}