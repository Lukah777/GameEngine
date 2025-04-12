#pragma once
#include "Component.h"

namespace Engine
{
    class PositionComponent: public Component
    {
    private:
        double m_x = 0;
        double m_y = 0;
        double m_angle = 0;
        double m_oldAngle = 0;
    public:
        PositionComponent(System* pSystem, GameObject* pGameObject, double x, double y, double angle);
        double GetX();
        double GetY();
        void SetXY(double x, double y);
        double GetAngle();
        double GetOldAngle();
        void SetAngle(double angle);
        void SetOldAngle(double angle);
    };
};

