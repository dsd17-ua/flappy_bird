#pragma once
#include <memory>

class StateMachine;
struct Bird{
    float x;
    float y;
    float vy; // Velocidad vertical
};

class GameState
{

    public:
        GameState();
        virtual ~GameState() = default;

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        void setStateMachine(StateMachine* stt_mch) {state_machine = stt_mch;}

    protected:
        StateMachine* state_machine;
        Bird bird;
        const float GRAVEDAD = 600.0f; // Aceleración debida a la gravedad (pixels/seg^2)
};