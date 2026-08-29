#include "Game.h"

// Inicialização variáveis estáticas
Game* Game::instance = nullptr;

// Métodos
Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        return;
    }

    instance = this;

    // TODO: tratamento erros inicialização

    /* Inicializa todas as bibliotecas */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
    TTF_Init();

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    state = new State();
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
    bool quitRequested = state->QuitRequested();

    while (!quitRequested) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
        quitRequested = state->QuitRequested();
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

Game& Game::GetInstance() {
    if (instance == nullptr) {  // se não foi instanciado
        instance = new Game("221020940", 1200, 900);
    }

    return *instance;
}
