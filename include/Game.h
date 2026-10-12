#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL

#include <iostream>
#include <string>

#include "InputManager.h"
#include "SDL_include.h"
#include "State.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class State;

// Game é responsável por inicializar recursos, rodar o loop principal do
// jogo e liberar os recursos quando o jogo for encerrado;
//
// A classe Game implementa as funções básicas da nossa engine,
// incluindo o main game loop, e a inicialização dos subsistemas (no caso, SDL,
// SDL_image e SDL_mixer) que precisaremos para outras classes
// funcionarem
class Game {
   public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime();

   private:
    Game(std::string title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    InputManager* input;
    void CalculateDeltaTime();

    Uint32 frameStart;
    float dt;
};

#endif