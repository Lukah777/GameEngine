#include "HeroComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"

Engine::HeroComponent::HeroComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
    m_pSystem = pSystem;
}

void Engine::HeroComponent::HandleMessage(Engine::Message msg)
{
    if (msg.m_pRecipiant == GetOwner())
    {
        if (msg.m_msg == (const char*)"Collision" && msg.m_pSender->GetComponent("EnemyComponent") != nullptr)       //Check if Enemy
        {
            GetMessageSys()->SendMsg("Destroy", GetOwner(), GetOwner());
        }

        if (msg.m_msg == (const char*)"Collision")
        {
            PhysicsComponent* pPhysComp = dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"));
            PositionComponent* pPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
            double oldAngle = pPosComp->GetOldAngle();
            pPosComp->SetAngle(oldAngle);

            if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_W_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, 2);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_A_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 2, 0);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_S_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, -2);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_D_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, -2, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 0.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 1, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 90.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, 1);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 180.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, -1, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 270.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, -1);
            }
        }
    }
}
