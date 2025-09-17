#pragma once
#include "GameState.hpp"
extern "C" {
    #include <raylib.h>
}


class MainMenuState : public GameState
{
    public:
        MainMenuState();
        ~MainMenuState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        const float RADIO_PAJARO = 17.0f;
};