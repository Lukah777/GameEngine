#include "CollisionComponent.h"
#include "GameObject.h"
#include "SDL.h"
#include "PositionComponent.h"
#include "ImageComponent.h"
#include "PhysicsComponent.h"

Engine::CollisionComponent::CollisionComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::CollisionComponent::Update(System* pSystem)
{
    /*
    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    int ownerX = pOwnerPosComp->GetX();
    int ownerY = pOwnerPosComp->GetY();
    int numCells = pSystem->GetNumCells();
    
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
                //GetMessageSys()->SendMsg("Collision", GetOwner(), pObject);
            }
        }
    }
    */
    return true;
}