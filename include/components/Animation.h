#ifndef ANIMATION_H
#define ANIMATION_H

// Classe usada nos componentes para facilitar o gerenciamento de troca de animações.
// Ela nada mais é do que um conjunto de números que representa o primeiro e último frames da animação, e quanto tempo deve se passar em cada frame.
class Animation {
   public:
    Animation(int frameStart, int frameEnd, float frameTime);

    int frameStart;
    int frameEnd;
    int frameTime;
};

#endif