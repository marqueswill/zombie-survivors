#include "components/Animator.h"

#include "components/SpriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated),
      frameStart(0),
      frameEnd(0),
      frameTime(0),
      currentFrame(0),
      timeElapsed(0) {
}

void Animator::Update(float dt) {
    if (frameTime == 0) {
        return;
    }

    timeElapsed++;

    if (timeElapsed > frameTime) {
        currentFrame = (currentFrame > frameEnd) ? frameStart : currentFrame + 1;
        timeElapsed -= frameTime;
    }

    SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
    if (sprite != nullptr) {
        sprite->SetFrame(currentFrame);
    }
}

void Animator::Render() {}

void Animator::SetAnimation(std::string name) {
    auto it = animations.find(name);

    if (it == animations.end()) {
        return;
    }

    Animation animation = it->second;

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