#include "TeleporterComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "SDL.h"
#include "ImageComponent.h"
#include "HeroComponent.h"
#include "AIComponent.h"
#include <random>
#include <time.h>
Engine::TeleporterComponent::TeleporterComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::TeleporterComponent::Update(Engine::System* pSystem)
{
    srand(time(NULL));

    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    int ownerX = pOwnerPosComp->GetX();
    int ownerY = pOwnerPosComp->GetY();

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
        if (pObject == nullptr)
            break;
        HeroComponent* pOtherHeroComp = static_cast<HeroComponent*>(pObject->GetComponent("HeroComponent"));
        AIComponent* pOtherEnemyComp = static_cast<AIComponent*>(pObject->GetComponent("AIComponent"));
        if (pOtherHeroComp == nullptr)
        {
            if (pOtherEnemyComp == nullptr)
                continue;
        }

        if (pObject != GetOwner())
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
                int randLoc = rand() % 3;
                if (randLoc == 0)
                {
                    pObjectPosComp->SetXY(65, 385);
                }
                else if (randLoc == 1)
                {
                    pObjectPosComp->SetXY(385, 337);
                }
                else if (randLoc == 2)
                {
                    pObjectPosComp->SetXY(385, 97);
                }
                else if (randLoc == 3)
                {
                    pObjectPosComp->SetXY(113, 146);
                }
            }
        }
    }
    return true;
}
