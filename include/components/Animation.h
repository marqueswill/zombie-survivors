#ifndef ANIMATION_H
#define ANIMATION_H

#define INCLUDE_SDL
#include "SDL_include.h"

// Classe usada nos componentes para facilitar o gerenciamento de troca de animações.
// Ela nada mais é do que um conjunto de números que representa o primeiro e último frames da animação, e quanto tempo deve se passar em cada frame.
class Animation {
   public:
    Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;
};

#endif