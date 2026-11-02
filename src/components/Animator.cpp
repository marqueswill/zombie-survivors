#include "components/Animator.h"

#include "components/SpriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated),
      frameStart(0),
      frameEnd(0),
      frameTime(0),
      currentFrame(0),
      timeElapsed(0),
      current("") {
}

void Animator::Update(float dt) {
    if (frameTime <= 0) {
        return;
    }

    timeElapsed += dt;
    bool changed = false;

    while (timeElapsed >= frameTime) {
        timeElapsed -= frameTime;
        currentFrame++;

        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        changed = true;
    }

    if (changed) {
        SpriteRenderer* sprite =
            associated.GetComponent<SpriteRenderer>();

        if (sprite != nullptr) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::Render() {}

void Animator::SetAnimation(std::string name) {
    // Se já está tocando essa animação, não reinicia
    if (name == current) {
        return;
    }

    auto it = animations.find(name);

    Animation animation = it->second;

    current = name;
    frameStart = animation.frameStart;
    frameEnd = animation.frameEnd;
    frameTime = animation.frameTime;
    currentFrame = frameStart;
    timeElapsed = 0;

    SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
    if (sprite != nullptr) {
        sprite->SetFrame(currentFrame);
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    // Se animation já existir, não faz nada
    if (animations.find(name) != animations.end()) {
        return;
    }

    animations.insert<std::pair<std::string, Animation>>({name, anim});
}