#include "GameObject.h"

#include "Component.h"

GameObject::GameObject() : isDead(false) {
    box = Rect();
    components = {};
};

GameObject::~GameObject() {
    // Faz delete de trás pra frente
    for (int i = components.size() - 1; i >= 0; i--) {
        delete *(components.begin() + i);
    }
    components.clear();
};

// Percorre o vetor de componentes chamando o Update(dt) dos mesmos.
void GameObject::Update(float dt) {
    for (auto& cpt : components) {
        cpt->Update(dt);
    }
}

// Percorre o vetor de componentes chamando o Render dos mesmos
void GameObject::Render() {
    for (auto& cpt : components) {
        cpt->Render();
    }
}

// Retorna isDead
bool GameObject::IsDead() {
    return isDead;
}

// Atribui verdadeiro a isDead
void GameObject::RequestDelete() {
    isDead = true;
}

// Adiciona o componente ao vetor de componentes
void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

// Remove o componente do vetor de componentes se ele estiver lá
void GameObject::RemoveComponent(Component* targetCpt) {
    components.erase(std::remove(components.begin(), components.end(), targetCpt), components.end());
}
