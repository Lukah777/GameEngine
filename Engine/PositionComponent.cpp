#include "PositionComponent.h"

Engine::PositionComponent::PositionComponent(System* pSystem, GameObject* pGameObject, double x, double y, double angle)
    :Component(pSystem, pGameObject)
{
    m_x = x;
    m_y = y;
    m_angle = angle;
}

double Engine::PositionComponent::GetX()
{
    return m_x;
}

double Engine::PositionComponent::GetY()
{
    return m_y;
}

void Engine::PositionComponent::SetXY(double x, double y)
{
    m_x = x;
    m_y = y;
}

double Engine::PositionComponent::GetAngle()
{
    return m_angle;
}

double Engine::PositionComponent::GetOldAngle()
{
    return m_oldAngle;
}

void Engine::PositionComponent::SetAngle(double angle)
{
    m_angle =  angle;
}

void Engine::PositionComponent::SetOldAngle(double angle)
{
    m_oldAngle = m_angle;
}

