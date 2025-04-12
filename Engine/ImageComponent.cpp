#include "ImageComponent.h"
#include "SDL.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "HeroComponent.h"

Engine::ImageComponent::ImageComponent(System* pSystem, GameObject* pGameObject, const char* fileName)
    :Component(pSystem, pGameObject)
{
    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    if (fileName != nullptr)
    {
        m_pImage = pResources->GetImageData(fileName, pGraphics->GetRender());
    }
}

void Engine::ImageComponent::Render(Engine::System* pSystem)
{
    PositionComponent* PosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    Graphics* pGraphics = pSystem->GetGraphics();
    if (PosComp != nullptr)
        pGraphics->DrawImage(this->GetImage(), (int)PosComp->GetX(), (int)PosComp->GetY(), nullptr, PosComp->GetAngle());
}