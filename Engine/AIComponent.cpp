#include "AIComponent.h"
#include "HeroComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "ImageComponent.h"
#include "SDL.h"
#include "CollisionComponent.h"
#include "EnemyBulletComponent.h"
#include <string.h> 

Engine::AIComponent::AIComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
    m_lastDirX = 0;
    m_lastDirY = 0;
}

bool Engine::AIComponent::Update(Engine::System* pSystem)
{
    double moveSpeed = 1;
    double VelX = 0;
    double VelY = 0;
    bool inRange = false;

    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    PositionComponent* pTargetPosComp = nullptr;

    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        if (pObject == nullptr)
            break;
        HeroComponent* pHeroComp = static_cast<HeroComponent*>(pObject->GetComponent("HeroComponent"));

        if (pHeroComp == nullptr)
            continue;

        pTargetPosComp = static_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));


        //
        if (pOwnerPosComp->GetX() < pTargetPosComp->GetX())
        {
            VelX = moveSpeed;
        }
        else if (pOwnerPosComp->GetX() > pTargetPosComp->GetX())
        {
            VelX = -moveSpeed;
        }
       
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, VelX, 0);


        int ownerX = (int)pOwnerPosComp->GetX();
        int ownerY = (int)pOwnerPosComp->GetY();

        SDL_Rect OwnerRect;
        Image* pOwnerImg = static_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"))->GetImage();
        OwnerRect.x = ownerX;
        OwnerRect.y = ownerY;
        OwnerRect.w = pOwnerImg->GetW();
        OwnerRect.h = pOwnerImg->GetH();

        for (int j = 0; j < pSystem->GetGameObjectSize(); j++)
        {
            GameObject* pObjectNew = nullptr;
            pObjectNew = pSystem->GetGameObjectAt(j);
            CollisionComponent* pOtherCollisionComp = static_cast<CollisionComponent*>(pObjectNew->GetComponent("CollisionComponent"));
            if (pObjectNew == nullptr)
                break;

            if (pOtherCollisionComp != nullptr && pObjectNew != GetOwner() && pObjectNew->GetComponent("CollisionComponent") != nullptr)
            {
                SDL_Rect ObjectRect;
                PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObjectNew->GetComponent("PositionComponent"));
                Image* pObjectImg = static_cast<ImageComponent*>(pObjectNew->GetComponent("ImageComponent"))->GetImage();
                ObjectRect.x = (int)pObjectPosComp->GetX();
                ObjectRect.y = (int)pObjectPosComp->GetY();
                ObjectRect.w = pObjectImg->GetW();
                ObjectRect.h = pObjectImg->GetH();


                if (SDL_HasIntersection(&ObjectRect, &OwnerRect) == SDL_TRUE)
                {
                    dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, -VelX, 0);
                    VelX = 0;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObjectNew = nullptr;
        pObjectNew = pSystem->GetGameObjectAt(i);
        if (pObjectNew == nullptr)
            break;
        HeroComponent* pHeroComp = static_cast<HeroComponent*>(pObjectNew->GetComponent("HeroComponent"));

        if (pHeroComp == nullptr)
            continue;

        PositionComponent* pTargetPosComp = static_cast<PositionComponent*>(pObjectNew->GetComponent("PositionComponent"));

        if (pOwnerPosComp->GetY() < pTargetPosComp->GetY())
        {
            VelY = moveSpeed;
        }
        else if (pOwnerPosComp->GetY() > pTargetPosComp->GetY())
        {
            VelY = -moveSpeed;
        }
        
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, 0, VelY);

        int ownerX = (int)pOwnerPosComp->GetX();
        int ownerY = (int)pOwnerPosComp->GetY();

        SDL_Rect OwnerRect;
        Image* pOwnerImg = static_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"))->GetImage();
        OwnerRect.x = ownerX;
        OwnerRect.y = ownerY;
        OwnerRect.w = pOwnerImg->GetW();
        OwnerRect.h = pOwnerImg->GetH();

        for (int j = 0; j < pSystem->GetGameObjectSize(); j++)
        {
            GameObject* pObjectNew = nullptr;
            pObjectNew = pSystem->GetGameObjectAt(j);
            CollisionComponent* pOtherCollisionComp = static_cast<CollisionComponent*>(pObjectNew->GetComponent("CollisionComponent"));
            if (pObjectNew == nullptr)
                break;

            if (pOtherCollisionComp != nullptr && pObjectNew != GetOwner() && pObjectNew->GetComponent("CollisionComponent") != nullptr)
            {
                SDL_Rect ObjectRect;
                PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObjectNew->GetComponent("PositionComponent"));
                Image* pObjectImg = static_cast<ImageComponent*>(pObjectNew->GetComponent("ImageComponent"))->GetImage();
                ObjectRect.x = (int)pObjectPosComp->GetX();
                ObjectRect.y = (int)pObjectPosComp->GetY();
                ObjectRect.w = pObjectImg->GetW();
                ObjectRect.h = pObjectImg->GetH();


                if (SDL_HasIntersection(&ObjectRect, &OwnerRect) == SDL_TRUE)
                {
                    dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, 0, -VelY);
                    VelY = 0;
                    break;
                }
            }
        }
        if (abs(pTargetPosComp->GetX() - pOwnerPosComp->GetX()) < 100 && abs(pTargetPosComp->GetY() - pOwnerPosComp->GetY()) < 100)
            inRange = true;

        if (VelX > 0)
        {
            pOwnerPosComp->SetAngle(0);
        }
        if (VelX < 0)
        {
            pOwnerPosComp->SetAngle(180);
        }
        if (VelY > 0)
        {
            pOwnerPosComp->SetAngle(90);
        }
        if (VelY < 0)
        {
            pOwnerPosComp->SetAngle(270);
        }
    }

    if (inRange)
    {
        double directionX = 0;
        double directionY = 0;

        if (VelX > 0)
        {
            directionX = 1;
            //pSystem->GetLog()->PrintLog("right");
        }
        else if (VelX < 0)
        {
            directionX = -1;
            //pSystem->GetLog()->PrintLog("left");
        }
        //pSystem->GetLog()->PrintLog("X: " + std::to_string(VelX));
        else if (VelY > 0)
        {
            directionY = 1;
            //pSystem->GetLog()->PrintLog("down");
        }
        else if (VelY < 0)
        {
            directionY = -1;
            //pSystem->GetLog()->PrintLog("up");
        }
        else
        {
            if (pTargetPosComp->GetX() > pOwnerPosComp->GetX())
            {
                directionX = 1;
            }
            else if (pTargetPosComp->GetX() < pOwnerPosComp->GetX())
            {
                directionX = -1;
            }
            else if (pTargetPosComp->GetY() > pOwnerPosComp->GetY())
            {
                directionY = 1;
            }
            else if (pTargetPosComp->GetY() < pOwnerPosComp->GetY())
            {
                directionY = -1;
            }
        }
        //pSystem->GetLog()->PrintLog("Y: " + std::to_string(VelY));

        if ((directionX != 0) || (directionY != 0))
        {
            for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
            {
                GameObject* pObject = nullptr;
                pObject = pSystem->GetGameObjectAt(i);
                EnemyBulletComponent* pBulletComp = static_cast<EnemyBulletComponent*>(pObject->GetComponent("EnemyBulletComponent"));
                if (pObject == nullptr)
                    break;

                if (pBulletComp != nullptr && pObject != GetOwner() && pObject->GetComponent("CollisionComponent") != nullptr && pBulletComp->GetTimer() > 120)
                {
                    PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
                    pObjectPosComp->SetXY(pOwnerPosComp->GetX() + 16 + directionX * 26 - 5, pOwnerPosComp->GetY() + 16 + directionY * 26 -5);
                    pBulletComp->SetDirection(directionX, directionY);
                    if (directionX > 0)
                    {
                        pObjectPosComp->SetAngle(0);
                    }
                    if (directionX < 0)
                    {
                        pObjectPosComp->SetAngle(180);
                    }
                    if (directionY > 0)
                    {
                        pObjectPosComp->SetAngle(90);
                    }
                    if (directionY < 0)
                    {
                        pObjectPosComp->SetAngle(270);
                    }
                    //pSystem->GetLog()->PrintLog("Bullet " + std::to_string(pObjectPosComp->GetX()) + " " + std::to_string(pObjectPosComp->GetY()));
                    //pSystem->GetLog()->PrintLog("Tank " + std::to_string(pOwnerPosComp->GetX()) + " " + std::to_string(pOwnerPosComp->GetY()));
                }
            }
        }
    }
    
    return true;
}
