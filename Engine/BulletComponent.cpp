#include "BulletComponent.h"
#include "PositionComponent.h"
#include "ImageComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SDL.h"
#include "JNMath.h"

Engine::BulletComponent::BulletComponent(System* pSystem, GameObject* pGameObject, double velocityX, double velocityY)
    :Component(pSystem, pGameObject)
{
    m_directionX = velocityX;
    m_directionY = velocityY;
}

bool Engine::BulletComponent::Update(Engine::System* pSystem)
{
    m_timer++;

    double bulletSpeed = 1.5;

    dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, m_directionX * bulletSpeed , m_directionY * bulletSpeed);

    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    if (m_timer > 120)
    {
        pOwnerPosComp->SetXY(-100, -100);
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
            ObjectRect.x = (int)pObjectPosComp->GetX();
            ObjectRect.y = (int)pObjectPosComp->GetY();
            ObjectRect.w = pObjectImg->GetW();
            ObjectRect.h = pObjectImg->GetH();


            if (SDL_HasIntersection(&ObjectRect, &OwnerRect) == SDL_TRUE)
            {
                if (pObject->GetComponent("EnemyComponent") != nullptr)
                {
                    pObjectPosComp->SetXY(-100, -200);
                    break;
                }

                double normX = 0;
                double normY = 0;
                if (OwnerRect.x + OwnerRect.w - bulletSpeed - 1 <= ObjectRect.x) //right wall
                {
                    normX = -1;
                }
                else if (OwnerRect.x + bulletSpeed + 1 >= ObjectRect.x + ObjectRect.w) //left wall
                {
                    normX = 1;
                }
                else if (OwnerRect.y + bulletSpeed + 1 >= ObjectRect.y + ObjectRect.h) //top wall
                {
                    normY = 1;
                }
                else if (OwnerRect.y + OwnerRect.h - bulletSpeed -1 <= ObjectRect.y) //bottom wall
                {
                    normY = -1;
                }
                Vec2 ballVect(m_directionX, m_directionY);
                Vec2 normalVect(normX, normY);
                Vec2 newVect = Bounce2D<double>(ballVect, normalVect);
                m_directionX = newVect.x;
                m_directionY = newVect.y;

                //$ handle edge cases where if bounces off the wrong type of wall or corners and bounces the wrong direction, thru moving and added wall hit boes
            }
        }
    }

    return true;
}

void Engine::BulletComponent::SetDirection(double velocityX, double velocityY)
{
    m_directionX = velocityX;
    m_directionY = velocityY;
    m_timer = 0;
}
