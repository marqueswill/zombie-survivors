#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Rect.h"

class Component;

// GameObject é um agrupador de componentes.
// Todo GameObject (GO) possui uma posição no jogo (box).
class GameObject {
   public:
    GameObject();
    ~GameObject();

    Rect box;
    bool IsDead();

    void Update(float dt);
    void Render();
    void RequestDelete();

    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    template <typename T>
    T* GetComponent();

   private:
    std::vector<Component*> components;  // Lista de ponteiros para os components do game object
    bool isDead;                         // Flag para gerenciamento de components
};

// Retorna um ponteiro para o componente do tipo solicitado que estiver
// adicionado nesse objeto.
template <typename T>
T* GameObject::GetComponent() {
    long unsigned int index;
    for (index = 0; index < components.size(); index++) {
        T* component = dynamic_cast<T*>(components[index]);
        if (component != nullptr) {
            return component;
        }
    }
    return nullptr;
}

#endif
