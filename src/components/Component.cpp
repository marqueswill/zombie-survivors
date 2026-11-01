#include "components/Component.h"

#include "GameObject.h"

Component::Component(GameObject& associated) : associated(associated) {
}

Component::~Component() {
}

// Chamado uma única vez, quando o GameObject é iniciado.
// Por padrão não faz nada; os componentes que precisarem sobrescrevem.
void Component::Start() {
}