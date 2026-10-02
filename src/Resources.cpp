#include "Resources.h"

#include <Game.h>
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);

    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();

    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: "
                  << IMG_GetError()
                  << std::endl;

        return nullptr;
    }

    imageTable[file] = texture;

    return texture;
}

void Resources::ClearImages() {
    for (auto& [file, texture] : imageTable) {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }

    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cerr << "Erro ao carregar musica: "
                  << Mix_GetError()
                  << std::endl;

        return nullptr;
    }

    musicTable[file] = music;

    return music;
}

void Resources::ClearMusics() {
    for (auto& [file, music] : musicTable) {
        if (music != nullptr) {
            Mix_FreeMusic(music);
        }
    }

    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

    if (sound == nullptr) {
        std::cerr << "Erro ao carregar som: "
                  << Mix_GetError()
                  << std::endl;

        return nullptr;
    }

    soundTable[file] = sound;

    return sound;
}

void Resources::ClearSounds() {
    for (auto& [file, sound] : soundTable) {
        if (sound != nullptr) {
            Mix_FreeChunk(sound);
        }
    }

    soundTable.clear();
}