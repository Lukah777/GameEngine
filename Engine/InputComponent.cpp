#include "InputComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "SDL.h"
#include "ImageComponent.h"
#include "CollisionComponent.h"

Engine::InputComponent::InputComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::InputComponent::Update(Engine::System* pSystem)
{
    double moveSpeed = 1;
    bool collide = false;

    PositionComponent* pPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    //if (pPosComp->GetAngle() != pPosComp->GetOldAngle())
        //pPosComp->SetOldAngle(pPosComp->GetAngle());

    //Update Input
    if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_ESCAPE_KEY))
        return false;

    if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_W_KEY))
    {
        //pPosComp->SetAngle(270);
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, 0.0, -moveSpeed);
    }
    else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_A_KEY))
    {
        //pPosComp->SetAngle(180);
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, -moveSpeed, 0.0);
    }
    else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_S_KEY))
    {
        //pPosComp->SetAngle(90);
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, 0.0, moveSpeed);
    }
    else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_D_KEY))
    {
        //pPosComp->SetAngle(0);
        dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, moveSpeed, 0.0);
    }

    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
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
                collide = true;
                PhysicsComponent* pPhysComp = dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"));

                if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_W_KEY))
                {
                    //pPosComp->SetAngle(pPosComp->GetOldAngle());
                    pPhysComp->ApplyVelocity(pSystem, 0.0, moveSpeed);
                }
                else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_A_KEY))
                {
                    //pPosComp->SetAngle(pPosComp->GetOldAngle());
                    pPhysComp->ApplyVelocity(pSystem, moveSpeed, 0.0);
                }
                else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_S_KEY))
                {
                    //pPosComp->SetAngle(pPosComp->GetOldAngle());
                    pPhysComp->ApplyVelocity(pSystem, 0.0, -moveSpeed);
                }
                else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_D_KEY))
                {
                    //pPosComp->SetAngle(pPosComp->GetOldAngle());
                    pPhysComp->ApplyVelocity(pSystem, -moveSpeed, 0.0);
                }
                    
                if (pPosComp->GetAngle() == 0.0)
                {
                    pPhysComp->ApplyVelocity(pSystem, moveSpeed, 0.0);
                }
                if (pPosComp->GetAngle() == 90.0)
                {
                    pPhysComp->ApplyVelocity(pSystem, 0.0, moveSpeed);
                }
                if (pPosComp->GetAngle() == 180.0)
                {
                    pPhysComp->ApplyVelocity(pSystem, -moveSpeed, 0.0);
                }
                if (pPosComp->GetAngle() == 270.0)
                {
                    pPhysComp->ApplyVelocity(pSystem, 0.0, -moveSpeed);
                }

                /////// Second collison Check
                PositionComponent* pPosCompNew = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

                PositionComponent* pOwnerPosCompNew = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
                int ownerXNew = (int)pOwnerPosCompNew->GetX();
                int ownerYNew = (int)pOwnerPosCompNew->GetY();

                SDL_Rect OwnerRectNew;
                Image* pOwnerImgNew = static_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"))->GetImage();
                OwnerRectNew.x = ownerXNew;
                OwnerRectNew.y = ownerYNew;
                OwnerRectNew.w = pOwnerImgNew->GetW();
                OwnerRectNew.h = pOwnerImgNew->GetH();

                for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                {
                    GameObject* pObjectNew = nullptr;
                    pObjectNew = pSystem->GetGameObjectAt(i);
                    CollisionComponent* pOtherCollisionCompNew = static_cast<CollisionComponent*>(pObjectNew->GetComponent("CollisionComponent"));
                    if (pObjectNew == nullptr)
                        break;

                    if (pOtherCollisionCompNew != nullptr && pObjectNew != GetOwner() && pObjectNew->GetComponent("CollisionComponent") != nullptr)
                    {
                        SDL_Rect ObjectRectNew;
                        PositionComponent* pOtherCollisionCompNew = static_cast<PositionComponent*>(pObjectNew->GetComponent("PositionComponent"));
                        Image* pObjectImgNew = static_cast<ImageComponent*>(pObjectNew->GetComponent("ImageComponent"))->GetImage();
                        ObjectRectNew.x = (int)pOtherCollisionCompNew->GetX();
                        ObjectRectNew.y = (int)pOtherCollisionCompNew->GetY();
                        ObjectRectNew.w = pObjectImgNew->GetW();
                        ObjectRectNew.h = pObjectImgNew->GetH();


                        if (SDL_HasIntersection(&ObjectRectNew, &OwnerRectNew) == SDL_TRUE)
                        {
                            PhysicsComponent* pPhysCompNew = dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"));

                            if (pPosCompNew->GetAngle() == 0.0)
                            {
                                pPhysCompNew->ApplyVelocity(pSystem, -moveSpeed, 0.0);
                            }
                            if (pPosCompNew->GetAngle() == 90.0)
                            {
                                pPhysCompNew->ApplyVelocity(pSystem, 0.0, -moveSpeed);
                            }
                            if (pPosCompNew->GetAngle() == 180.0)
                            {
                                pPhysCompNew->ApplyVelocity(pSystem, moveSpeed, 0.0);
                            }
                            if (pPosCompNew->GetAngle() == 270.0)
                            {
                                pPhysCompNew->ApplyVelocity(pSystem, 0.0, moveSpeed);
                            }
                            collide = false;


                            break;
                        }
                    }

                }
                break;
            }
        } 
    }

    if (!collide)
    {
        if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_W_KEY))
        {
            pPosComp->SetAngle(270);
        }
        else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_A_KEY))
        {
            pPosComp->SetAngle(180);
        }
        else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_S_KEY))
        {
            pPosComp->SetAngle(90);
        }
        else if (pSystem->GetInput()->GetIsKeyDown(pSystem->GetInput()->ENGINE_D_KEY))
        {
            pPosComp->SetAngle(0);
        }
    }

    return true;
}