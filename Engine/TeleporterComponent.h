#pragma once
#include "Component.h"
class GameObject;

namespace Engine
{
    class TeleporterComponent : public Component
    {
    public:
        TeleporterComponent (System* pSystem, GameObject* pGameObject );
        bool Update(Engine::System* pSystem) override;

    };
}


