#include "PhysicsComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"

Engine::PhysicsComponent::PhysicsComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

void Engine::PhysicsComponent::ApplyVelocity(System*, double x, double y)   
{
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));   
    if (posComp != nullptr)
        (posComp)->SetXY(posComp->GetX() + x, posComp->GetY() + y);               
}
