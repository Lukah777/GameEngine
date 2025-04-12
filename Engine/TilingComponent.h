#pragma once
#include "Component.h"
#include "TMXParser.h"

namespace Engine
{
    struct Rect
    {
        int x;
        int y;
        int w;
        int h;
    };
    class TilingComponent : public Component
    {
        Image* m_pImage = nullptr;
    public:
        TilingComponent(System* pSystem, GameObject* pGameObject, const char* fileName);
        Image* GetImage() { return m_pImage; }
        void Render(Engine::System* pSystem);
    };
}


