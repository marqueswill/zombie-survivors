#include "Sound.h"

#include <Resources.h>

#include <iostream>

Sound::Sound() {
    chunk = nullptr;
    channel = -1;
}

Sound::Sound(std::string file) : Sound() {
    Open(file);
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Stop();
    }
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(channel, chunk, times - 1);
    }
}

void Sound::Stop() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    // if (chunk != nullptr) {
    //     Mix_FreeChunk(chunk);
    // }

    // chunk = Mix_LoadWAV(file.c_str());

    // // TODO: fazer tratamento de erro
    // if (chunk == nullptr) {
    //     std::cerr << "Erro ao carregar som (sound chunk): " << Mix_GetError() << std::endl;
    //     return;
    // }
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}
