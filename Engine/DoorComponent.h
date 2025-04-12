#pragma once
#include "Component.h"
namespace Engine
{
    class DoorComponent : public Component
    {
    public:
        DoorComponent(System* pSystem, GameObject* pGameObject);
    };
}


