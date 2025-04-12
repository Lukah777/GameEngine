#pragma once
#include "Component.h"
namespace Engine
{
    class PhysicsComponent : public Component
    {
    public:
        PhysicsComponent(System* pSystem, GameObject* pGameObject);
        void ApplyVelocity(Engine::System* pSystem, double x, double y);
    };
}


