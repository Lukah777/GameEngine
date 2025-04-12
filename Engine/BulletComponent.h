#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Engine {
    class BulletComponent :public Component
    {
    private:
        double m_directionX;
        double m_directionY;
        int m_timer =  130;
    public:
        BulletComponent(System* pSystem, GameObject* pGameObject, double velocityX = 0, double velocityY = 0);
        bool Update(Engine::System* pSystem) override;
        void SetDirection(double velocityX, double velocityY);
        int GetTimer() { return m_timer; };
    };
};