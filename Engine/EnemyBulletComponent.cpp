#include "EnemyBulletComponent.h"
#include "PositionComponent.h"
#include "ImageComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SDL.h"
#include "JNMath.h"

Engine::EnemyBulletComponent::EnemyBulletComponent(System* pSystem, GameObject* pGameObject, double velocityX, double velocityY)
    :Component(pSystem, pGameObject)
{
    m_directionX = velocityX;
    m_directionY = velocityY;
}

bool Engine::EnemyBulletComponent::Update(Engine::System* pSystem)
{
    m_timer++;

    double bulletSpeed = 1.5;

    dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, m_directionX * bulletSpeed, m_directionY * bulletSpeed);
     
    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    if (m_timer > 120)
    {
        pOwnerPosComp->SetXY(-200, -200);
        m_directionX = 0;
        m_directionY = 0;
        return true;
    }

    int ownerX = (int)pOwnerPosComp->GetX();
    int ownerY = (int)pOwnerPosComp->GetY();

    SDL_Rect OwnerRect;
    Image* pOwnerImg = static_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"))->GetImage();
    OwnerRect.x = ownerX;
    OwnerRect.y = ownerY;
    OwnerRect.w = pOwnerImg->GetW();
    OwnerRect.h = pOwnerImg->GetH();

    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        CollisionComponent* pOtherCollisionComp = static_cast<CollisionComponent*>(pObject->GetComponent("CollisionComponent"));
        if (pObject == nullptr)
            break;

        if (pOtherCollisionComp != nullptr && pObject != GetOwner() && pObject->GetComponent("CollisionComponent") != nullptr)
        {
            SDL_Rect ObjectRect;
            PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
            Image* pObjectImg = static_cast<ImageComponent*>(pObject->GetComponent("ImageComponent"))->GetImage();
            ObjectRect.x = pObjectPosComp->GetX();
            ObjectRect.y = pObjectPosComp->GetY();
            ObjectRect.w = pObjectImg->GetW();
            ObjectRect.h = pObjectImg->GetH();


            if (SDL_HasIntersection(&ObjectRect, &OwnerRect) == SDL_TRUE)
            {
                pOwnerPosComp->SetXY(-200, -200);
                if (pObject->GetComponent("HeroComponent") != nullptr)
                {
                    pObjectPosComp->SetXY(-300, -300);
                    break;
                }               
            }
        }
    }

    return true;
}

void Engine::EnemyBulletComponent::SetDirection(double velocityX, double velocityY)
{
    m_directionX = velocityX;
    m_directionY = velocityY;
    m_timer = 0;
}
