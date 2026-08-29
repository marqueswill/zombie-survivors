#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

// A classe Sprite encapsula o carregamento e uso de SDL_Textures, o tipo da SDL que contém uma imagem carregada do disco pronta para ser renderizada num SDL_Renderer.Sprite tem quatro atributos :
// - texture : A imagem em si
// - width, height : As dimensões da imagem
// - clipRect : O retângulo de clipping(determina uma parte específica da imagem para ser renderizada)
class Sprite {
   public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

   private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif