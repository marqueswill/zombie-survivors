#include "Sprite.h"

#include <Resources.h>

#include "Game.h"

Sprite::Sprite()
    : width(0), height(0), frameCountW(1), frameCountH(1), texture(nullptr), clipRect{0, 0, 0, 0} {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : width(0),
      height(0),
      frameCountW(frameCountW),
      frameCountH(frameCountH),
      texture(nullptr),
      clipRect{0, 0, 0, 0} {
    Open(file);
}

// Se houver imagem alocada, desaloca. Nunca use delete ou free em
// uma SDL_Texture.Use SDL_DestroyTexture(SDL_Texture*)
Sprite::~Sprite() {
    // if (texture != nullptr) {
    //     SDL_DestroyTexture(texture);
    // }
}

int Sprite::GetWidth() {
    return clipRect.w;
}

int Sprite::GetHeight() {
    return clipRect.h;
}

// Seleciona qual sub-região da imagem (spritesheet) será exibida
void Sprite::SetFrame(int frame) {
    if (frame < 0 || frameCountW <= 0 || frameCountH <= 0 || width <= 0 || height <= 0) {
        return;
    }

    // Descobre o tamanho do frame
    int frameWidth = width / frameCountW;    // Tamanho da imagem dividido pelo numero de colunas
    int frameHeight = height / frameCountH;  // Tamanho da imagem dividido pelo numero de linhas

    int linhasAPular = frame / frameCountW;   // Offset altura
    int colunasAPular = frame % frameCountW;  // Offset largura

    // Coordenadas x e y iniciais do frame
    int x = colunasAPular * frameWidth;  // Offset horizontal
    int y = linhasAPular * frameHeight;  // Offset vertical

    if ((x >= 0 && y >= 0) &&
        ((x + frameWidth) <= width) &&           // Não pode ultrapassar o width do sprite
        ((y + frameHeight) <= height)) {         // Não pode ultrapassar o height do sprite
        SetClip(x, y, frameWidth, frameHeight);  // Faz o "recorte" do spritesheet
    }
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    if (frameCountW <= 0 || frameCountH <= 0) {
        return;
    }

    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
};

// Retorna true se texture estiver alocada
bool Sprite::IsOpen() {
    return texture != nullptr;
}

// Carrega a imagem indicada pelo caminho file. Antes de carregar, deve-se checar
// se já há alguma imagem carregada em texture. Se sim, deve ser desalocada primeiro.
void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    // Se nao conseguir abrir imagem ou nao conseguir fazer query no sdl
    if (texture == nullptr ||
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        texture = nullptr;
        width = 0;
        height = 0;
        clipRect = {0, 0, 0, 0};
        return;
    }

    SetFrame(0);
}

// Seta clipRect com os parâmetros dados
void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos.
// - SDL_Renderer* renderer: O renderizador de Game.
// - SDL_Texture* texture: A textura a ser renderizada;
// - SDL_Rect* srcrect: O retângulo de clipagem. Especifica uma área da
// textura a ser "recortada" e renderizada.
// - SDL_Rect* dstrect: O retângulo destino. Determina a posição na tela
// em que a textura deve ser renderizada (membros x e y). Se os
// membros w e h diferirem das dimensões do clip, causarão uma
// mudança na escala, contraindo ou expandindo a imagem para se
// adaptar a esses valores
void Sprite::Render(int x, int y, int w, int h) {
    if (texture == nullptr) {
        return;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect dstrect = SDL_Rect();

    dstrect.x = x;
    dstrect.y = y;

    dstrect.w = (w > 0) ? w : clipRect.w;
    dstrect.h = (h > 0) ? h : clipRect.h;

    SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
}
