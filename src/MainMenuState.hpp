#pragma once
#include "GameState.hpp"



class MainMenuState : public GameState
{
    public:
        MainMenuState();
        ~MainMenuState();

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        const float RADIO_PAJARO = 17.0f;
        std::deque<PipePair> pipes;
         float PIPE_W = 32.0f;
         float PIPE_H = 320.0f;
        const float PIPE_SPEED = 120.0f; // Velocidad a la que se mueven las tuberías (pixels/seg)
        const float SPAWN_EVERY = 1.5f; // Cada cuantos segundos aparece un nuevo par de tuberías
        float spawnTimer = 0.0f;
         float PIPE_GAP = 100.0f; // Espacio vertical entre las tuberías superior e inferior
        int score=0; // Puntuación del jugador

        Texture2D birdSprite;
        Texture2D pipeSprite;
        
};