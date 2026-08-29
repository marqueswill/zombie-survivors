#include "Game.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "SDL_include.h"

// Inicialização variáveis estáticas
Game* Game::instance = nullptr;

// Métodos

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {  // Garante que só exista um objeto dessa classe
        return;
    }

    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        std::cerr << "Erro ao inicializar SDL_image: " << IMG_GetError() << std::endl;
    }

    int mixFlags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG;
    if ((Mix_Init(mixFlags) & mixFlags) == 0) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Erro ao abrir áudio: " << Mix_GetError() << std::endl;
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
    }

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

// Run é um simples loop, que funciona enquanto QuitRequested não
// retornar true.
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

// Retorna o membro renderer.
SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

// Retorna *state.
State& Game::GetState() {
    return *state;
}

// Força o padrão singleton para classe Game
Game& Game::GetInstance() {
    if (instance == nullptr) {  // se não foi instanciado
        instance = new Game("221020940", 1200, 900);
    }

    return *instance;
}
