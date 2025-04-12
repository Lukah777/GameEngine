#pragma once
#include "Component.h"
namespace Engine {
    class AIComponent : public Component
    {
    private:
        int m_lastDirX = 0;
        int m_lastDirY = 0;
    public:
        AIComponent(System* pSystem, GameObject* pGameObject);
        bool Update(Engine::System* pSystem) override;
    };
}


