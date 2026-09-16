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
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h);

    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

   private:
    int width;
    int height;
    int frameCountW;  // numero de colunas
    int frameCountH;  // numero de linhas
    SDL_Texture* texture;
    SDL_Rect clipRect;
};

#endif