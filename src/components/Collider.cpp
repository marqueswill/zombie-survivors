#include "components/Collider.h"

#include <cmath>

#ifdef DEBUG
#define INCLUDE_SDL
#include "Camera.h"
#include "Game.h"
#include "SDL_include.h"
#endif  // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset) {
}

// Copia a box do objeto, aplica a escala e centraliza no centro do objeto
// somado ao offset rotacionado pelo ângulo dele.
void Collider::Update(float dt) {
    (void)dt;

    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;

    Vec2 center = associated.box.getCenter() + offset.rotate(associated.angleDeg * M_PI / 180);
    box.x = center.x - box.w / 2;
    box.y = center.y - box.h / 2;
}

// Em modo debug, desenha a caixa de colisão em vermelho
void Collider::Render() {
#ifdef DEBUG
    Vec2 center(box.getCenter());
    float angle = associated.angleDeg * M_PI / 180;
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).rotate(angle) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).rotate(angle) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).rotate(angle) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).rotate(angle) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif  // DEBUG
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}