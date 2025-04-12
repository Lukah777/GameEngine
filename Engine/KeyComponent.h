#pragma once
#include "Component.h"
namespace Engine
{
    class KeyComponent : public Component
    {
    public:
        KeyComponent(System* pSystem, GameObject* pGameObject);
    };
}


