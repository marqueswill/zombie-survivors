#include "Game.h"

// Inicialização variáveis estáticas
Game* Game::instance = nullptr;

// Métodos
Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        return;
    }

    instance = this;

    /* Inicializa todas as bibliotecas */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
    TTF_Init();

    SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int width, int height, Uint32 flags);
    SDL_Renderer* SDL_CreateRenderer(SDL_Window * window, int index, Uint32 flags);
}

Game::~Game() {
    if (state != nullptr) {
        delete state;
        state = nullptr;
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    /* Fecha todas (em ordem inversa de inicialização)*/
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    instance = nullptr;
}

void Game::Run() {
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

Game& Game::GetInstance() {
    if (instance == nullptr) {  // se não foi instanciado, cria o jogo
        instance = new Game("221020940", 1200, 900);
    }

    return *instance;  // retorna ponteiro
}
