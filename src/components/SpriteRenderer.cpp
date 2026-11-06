#include "components/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite() {
}

SpriteRenderer::SpriteRenderer(GameObject& associated,
                               std::string file,
                               int frameCountW,
                               int frameCountH,
                               bool cameraFollower)
    : Component(associated),
      sprite(file, frameCountW, frameCountH, cameraFollower) {
    // Altura e largura do box do GO são herdados do próprio sprite
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    SetFrame(0);
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

// Muda a escala do sprite e ajusta a box do GameObject, mantendo o
// centro no mesmo lugar
void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    Vec2 center = associated.box.getCenter();

    sprite.SetScale(scaleX, scaleY);

    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    associated.box.x = center.x - associated.box.w / 2;
    associated.box.y = center.y - associated.box.h / 2;
}

void SpriteRenderer::SetCameraFollower(bool cameraFollower) {
    sprite.SetCameraFollower(cameraFollower);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    sprite.Render(
        associated.box.x,
        associated.box.y,
        associated.box.w,
        associated.box.h,
        associated.angleDeg);
}
