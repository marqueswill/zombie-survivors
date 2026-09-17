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
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void Render(int x, int y, int w, int h);

   private:
    int width;             // Largura da imagem original
    int height;            // Altura da imagem original
    int frameCountW;       // Número de colunas na imagem
    int frameCountH;       // Número de linhas na imagem
    SDL_Texture* texture;  // Um ponteiro para a imagem real carregada na placa de vídeo
    SDL_Rect clipRect;     // Recorte da imagem original
};

#endif