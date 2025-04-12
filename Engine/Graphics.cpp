#include "Graphics.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Log.h"
#include "ResourceSystem.h"
#include "Image.h"
#include "TilingComponent.h"

void Engine::Graphics::CreateGraphics(Log* log, SDL_Window* pWindow)
{
    // Asign log pointer
    m_pLog = log;
    m_pSDLWindow = pWindow;
    // Attempts to create a hardware-accelerated renderer for our window.
    m_pSDLRenderer = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pSDLRenderer != nullptr)
    {
        // Print success message.
        m_pLog->PrintLog("SDL_CreateRenderer() succeeded.");
    }
    else
    {
        // Print error message. Remember to destroy window and quit SDL before exiting the program.
        m_pLog->PrintLog("SDL_CreateRenderer() failed. Error: ");
        m_pLog->PrintLog(SDL_GetError());
    }
}

void Engine::Graphics::CloseGraphics()
{
    SDL_DestroyRenderer(m_pSDLRenderer);
}
 
void Engine::Graphics::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(m_pSDLRenderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
    SDL_RenderDrawLine(m_pSDLRenderer, x1, y1, x2, y2);
}

void Engine::Graphics::Clear(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(m_pSDLRenderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
    SDL_RenderClear(m_pSDLRenderer);}

void Engine::Graphics::Present()
{
    SDL_RenderPresent(m_pSDLRenderer);
}

void Engine::Graphics::DrawImage(Image* pImage, int x, int y, Rect* pClip, double angle)
{
    SDL_Rect TempRect;
    SDL_Rect clipRect;
    if (pClip != nullptr)
    {
        TempRect = SDL_Rect{ x, y, pClip->w, pClip->h };
        clipRect = SDL_Rect{ pClip->x, pClip->y, pClip->w, pClip->h };
        SDL_RenderCopyEx(m_pSDLRenderer, pImage->GetSDLTexture(), &clipRect, &TempRect, angle, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        TempRect = SDL_Rect{ x, y, pImage->GetW(), pImage->GetH() };
        SDL_RenderCopyEx(m_pSDLRenderer, pImage->GetSDLTexture(), nullptr, &TempRect, angle, nullptr, SDL_FLIP_NONE);
    }


    
}


