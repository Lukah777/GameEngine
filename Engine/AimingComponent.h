#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Engine
{
    class AimingComponent : public Component
    {
        double m_vecX;
        double m_vecY;
    public:
        AimingComponent(System* pSystem, GameObject* pGameObject);
        bool Update(Engine::System* pSystem) override;
        void Shoot(Engine::System* pSystem);
    };
}

