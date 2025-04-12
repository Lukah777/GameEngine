#pragma once
#include "Component.h"

namespace Engine 
{
    class HeroComponent : public Component
    {
        bool m_collision = false;
        System* m_pSystem;
    public:
        HeroComponent(System* pSystem, GameObject* pGameObject);
        void HandleMessage(Engine::Message msg);
    };
}


