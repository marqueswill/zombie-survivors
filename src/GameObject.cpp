#include "GameObject.h"

#include "Component.h"

GameObject::GameObject() {
    isDead = false;
    box = Rect();
    components = {};
};

// Percorre vetor de components dando delete em todos e depois dando
// clear no vetor.
GameObject::~GameObject() {
    for (auto& cpt : components) {
        delete cpt;
    }
    components.clear();
};

void GameObject::Update(float dt) {
    for (auto& cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* targetCpt) {
    components.erase(std::remove(components.begin(), components.end(), targetCpt), components.end());
}
