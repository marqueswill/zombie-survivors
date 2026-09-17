#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

// Serve como wrapper para Sprite e simplificar o processo de renderizar todos os sprites do nosso jogo.
// Cada objeto com uma representação visual precisa de um componente que gerencie a sua renderização.
class SpriteRenderer : public Component {
   public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated,
                   std::string file,
                   int frameCountW = 1,
                   int frameCountH = 1);

    void Open(std::string file);
    void SetFrameCount(int frameCountW,
                       int frameCountH);
    void Update(float dt);
    void Render();
    void SetFrame(int frame);

   private:
    Sprite sprite;
};

#endif