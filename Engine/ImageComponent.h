#pragma once
#include "Component.h"

namespace Engine
{
    class ImageComponent : public Component
    {
    private:
        Image* m_pImage = nullptr;
    public:
        ImageComponent(System* pSystem, GameObject* pGameObject, const char* filename);
        Image* GetImage(){ return m_pImage; }
        void Render(Engine::System* pSystem);
    };
}


