#pragma once
#include "Component.h"

namespace Engine
{
    class DeathComponent : public Component
    {
    public:
        DeathComponent(System* pSystem, GameObject* pGameObject);
        void HandleMessage(Engine::Message msg);
    };
}

