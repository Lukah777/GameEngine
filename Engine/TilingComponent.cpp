#include "TilingComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include <SDL.h>
#include <SDL_image.h>

Engine::TilingComponent::TilingComponent(System* pSystem, GameObject* pGameObject, const char* fileName)
    :Component(pSystem, pGameObject)
{
    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    if (fileName != nullptr)
        m_pImage = pResources->GetImageData(fileName, pGraphics->GetRender());
}

void Engine::TilingComponent::Render(Engine::System* pSystem)
{
    TMXParser* pTMXParser = pSystem->GetResources()->GetTMXParser();
    int spriteSize = pTMXParser->GetSizeOfSprites();
    Rect TempRect;
    for (int y = 0; y < pTMXParser->GetHeight(); y++)
    {
        for (int x = 0; x < pTMXParser->GetWidth(); x++)
        {
            int index = x + y* pTMXParser->GetWidth();
            int yCord = y * spriteSize;
            int xCord = x * spriteSize;
            if (pTMXParser->GetBackgroundAtIndex(index) == 31)
            {
                TempRect = Rect{ 10 * spriteSize, 1 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 51)
            {
                TempRect = Rect{ 10 * spriteSize, 2 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 32)
            {
                TempRect = Rect{ 11 * spriteSize, 1 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 46)
            {
                TempRect = Rect{ 5 * spriteSize, 2 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 8)
            {
                TempRect = Rect{ 7 * spriteSize, 0 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 130)
            {
                TempRect = Rect{ 9 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 29)
            {
                TempRect = Rect{ 8 * spriteSize, 1 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 30)
            {
                TempRect = Rect{ 9 * spriteSize, 1 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 9)
            {
                TempRect = Rect{ 8 * spriteSize, 0 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 131)
            {
                TempRect = Rect{ 10 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 28)
            {
                TempRect = Rect{ 7 * spriteSize, 1 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 133)
            {
                TempRect = Rect{ 12 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 81)
            {
                TempRect = Rect{ 0 * spriteSize, 4 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 82)
            {
                TempRect = Rect{ 1 * spriteSize, 4 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 83)
            {
                TempRect = Rect{ 2 * spriteSize, 4 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 101)
            {
                TempRect = Rect{ 0 * spriteSize, 5 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 102)
            {
                TempRect = Rect{ 1 * spriteSize, 5 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 103)
            {
                TempRect = Rect{ 2 * spriteSize, 5 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 121)
            {
                TempRect = Rect{ 0 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 122)
            {
                TempRect = Rect{ 1 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 123)
            {
                TempRect = Rect{ 2 * spriteSize, 6 * spriteSize, spriteSize, spriteSize };
            }
            else if (pTMXParser->GetBackgroundAtIndex(index) == 11)
            {
                TempRect = Rect{ 10 * spriteSize, 0 * spriteSize, spriteSize, spriteSize };
            }
            pSystem->GetGraphics()->DrawImage(m_pImage, xCord, yCord, &TempRect);
        }
    } 
}
