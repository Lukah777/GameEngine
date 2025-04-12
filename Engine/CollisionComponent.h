#pragma once
#include "Component.h"
namespace Engine
{
    class CollisionComponent : public Component
    {
    public:
        CollisionComponent(System* pSystem, GameObject* pGameObject);
        bool Update(System* pSystem) override;
    };
}


