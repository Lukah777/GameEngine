#pragma once
#include "Component.h"
namespace Engine
{
    class EnemyComponent : public Component
    {
    public:
        EnemyComponent(System* pSystem, GameObject* pGameObject);
    };
}


