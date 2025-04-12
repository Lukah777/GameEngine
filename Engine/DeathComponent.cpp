#include "DeathComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"

Engine::DeathComponent::DeathComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

void Engine::DeathComponent::HandleMessage(Engine::Message msg)
{
    if (msg.m_msg == (const char*)"Destroy" && msg.m_pRecipiant == GetOwner())
    {
        PositionComponent* PosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
        if (PosComp)
            PosComp->SetXY(-100, -100);
    }
}