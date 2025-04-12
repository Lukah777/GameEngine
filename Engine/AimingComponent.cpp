#include "AimingComponent.h"
#include <SDL.h>
#include <math.h>
#include "PositionComponent.h"
#include "BulletComponent.h"

Engine::AimingComponent::AimingComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::AimingComponent::Update(Engine::System* pSystem)
{
    int x = 0;
    int y = 0;
    double directionX;
    double directionY;
    double angle;
    SDL_GetMouseState(&x, &y);

    PositionComponent* pPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        if (pObject == nullptr)
            break;

        if (pObject->GetComponent("HeroComponent") != nullptr)
        {
            PositionComponent* pHeroPosComp = dynamic_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
            pPosComp->SetXY(pHeroPosComp->GetX(), pHeroPosComp->GetY());

            x -= pPosComp->GetX();
            y -= pPosComp->GetY();

            pPosComp->SetAngle((atan2(y, x) * 180 / 3.14159));

            angle =pPosComp->GetAngle() * 3.14159 /180;
           
            directionX = cos(angle);
            directionY = sin(angle);
            //std::cout << offsetX << " " << offsetY << " " << angle << std::endl;

        }
    }

    if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_SPACE_KEY))
    {
        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = pSystem->GetGameObjectAt(i);
            BulletComponent* pBulletComp = static_cast<BulletComponent*>(pObject->GetComponent("BulletComponent"));
            if (pObject == nullptr)
                break;

            if (pBulletComp != nullptr && pObject != GetOwner() && pObject->GetComponent("CollisionComponent") != nullptr && pBulletComp->GetTimer() > 120)
            {
                PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
                pObjectPosComp->SetXY(pPosComp->GetX() + 16 + directionX * 26 -2.5, pPosComp->GetY() + 16 + directionY * 26 -2.5);
                pBulletComp->SetDirection(directionX, directionY);
            }
        }
    }

    return true;
}

void Engine::AimingComponent::Shoot(Engine::System* pSystem)
{
    int x = 0;
    int y = 0;
    double directionX;
    double directionY;
    double angle;
    SDL_GetMouseState(&x, &y);

    PositionComponent* pPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        if (pObject == nullptr)
            break;

        if (pObject->GetComponent("HeroComponent") != nullptr)
        {
            PositionComponent* pHeroPosComp = dynamic_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
            pPosComp->SetXY(pHeroPosComp->GetX(), pHeroPosComp->GetY());

            x -= pPosComp->GetX();
            y -= pPosComp->GetY();

            pPosComp->SetAngle((atan2(y, x) * 180 / 3.14159));

            angle = pPosComp->GetAngle() * 3.14159 / 180;

            directionX = cos(angle);
            directionY = sin(angle);
            //std::cout << offsetX << " " << offsetY << " " << angle << std::endl;

        }
    }
    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        BulletComponent* pBulletComp = static_cast<BulletComponent*>(pObject->GetComponent("BulletComponent"));
        if (pObject == nullptr)
            break;

        if (pBulletComp != nullptr && pObject != GetOwner() && pObject->GetComponent("CollisionComponent") != nullptr && pBulletComp->GetTimer() > 120)
        {
            PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pObject->GetComponent("PositionComponent"));
            pObjectPosComp->SetXY(pPosComp->GetX() + 16 + directionX * 26 - 2.5, pPosComp->GetY() + 16 + directionY * 26 - 2.5);
            pBulletComp->SetDirection(directionX, directionY);
        }
    }
}