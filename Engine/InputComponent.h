#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Engine {
    class InputComponent : public Component
    {
    public:
        InputComponent(System* pSystem, GameObject* pGameObject);
        bool Update(Engine::System* pSystem) override;
    };
}

