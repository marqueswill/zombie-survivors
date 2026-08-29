#include "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {
    Stop(0);
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}

// Mix_PlayMusic recebe uma música e quantas vezes ela deve ser
// tocada. Se loops for -1, a música repete infinitamente. Se loops for 0, a
// música não é tocada. Vale notar que a Mixer só suporta uma música sendo
// tocada por vez: Se outra música já estiver tocando, ela para.
// Não se esqueça que Mix_Music pode ser nullptr.
void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

// Mix_FadeOutMusic para a música atual dando um efeito de fade, isto
// é, diminuindo gradualmente o volume até chegar em 0. O tempo para a
// música parar totalmente é passado como argumento da função, em
// milissegundos. Vamos deixar default como 1,5 segundos. Caso queria que
// pare imediatamente, basta passar 0 como argumento
void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

// Carrega a música indicada no arquivo file. Lembre-se de tratar o caso
// em que nullptr é retornado
void Music::Open(std::string file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}
