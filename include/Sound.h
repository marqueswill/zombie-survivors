#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

#include <string>

// Sound é quase a mesma classe de Music, mesmo na implementação.
// As diferenças estão nas funções da Mixer usadas, e no fato de que, diferente
// das músicas, existem vários canais diferentes para reproduzir sons, e temos
// que manter registrado em qual canal o chunk está tocando para podermos
// pará-lo se necessário
class Sound {
   public:
    Sound();
    Sound(std::string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(std::string file);

    bool IsOpen();

   private:
    Mix_Chunk* chunk;
    int channel;
};

#endif
