#include "components/Collider.h"

#include <cmath>

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

void Collider::Render() {
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}