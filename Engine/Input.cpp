#include "Input.h"
#include <SDL.h>
#include "AimingComponent.h"
#include "System.h"

bool Engine::Input::GetIsKeyDown(keycode key)
{
    int Length;
    const Uint8* KeyboardState = SDL_GetKeyboardState(&Length);

    if (KeyboardState[key])
    {
        return true;
    }
    
    return false;
}

bool Engine::Input::Update(Engine::System* pSystem)
{
    SDL_Event event;           
    while (SDL_PollEvent(&event))
    {
        if (event.type == ENGINE_ESCAPE_KEY)
        {
            return false;
        }
        if (event.type == ENGINE_MOUSE_BUTTON)
        {
            for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
            {
                GameObject* pObject = nullptr;
                pObject = pSystem->GetGameObjectAt(i);
                if (pObject == nullptr)
                    break;

                AimingComponent* pAimComp = static_cast<AimingComponent*>(pObject->GetComponent("AimingComponent"));

                if (pAimComp != nullptr)
                {
                    pAimComp->Shoot(pSystem);
                }
            }
            return true;
        }
    }
    return true;
}