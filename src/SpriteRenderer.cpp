#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {
}

SpriteRenderer::SpriteRenderer(GameObject& associated,
                               std::string file,
                               int frameCountW = 1,
                               int frameCountH = 1) {}

void SpriteRenderer::Open(std::string file) {}
void SpriteRenderer::SetFrameCount(int frameCountW,
                                   int frameCountH) {}
void SpriteRenderer::Update(float dt) {}
void SpriteRenderer::Render() {}
void SpriteRenderer::SetFrame(int frame) {}