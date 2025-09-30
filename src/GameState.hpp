#pragma once
#include <memory>
#include <deque>
extern "C" {
    #include <raylib.h>
}

class StateMachine;
struct Bird{
    float x;
    float y;
    float vy; // Velocidad vertical
    //srpites
    int width;
    int height;
};

struct PipePair{
    Rectangle top;
    Rectangle bot;
    bool scored = false; // Para saber si ya se ha sumado el punto por pasar este par de tuberías

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