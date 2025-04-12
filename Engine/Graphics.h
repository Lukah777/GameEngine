#pragma once
#include <vector>
struct SDL_Renderer;
struct SDL_Window;

namespace Engine
{
    struct Rect;
    class Image;
    class Log;
    class Graphics
    {
    private:
        // Pointer to the renderer that can be used to draw output.
        SDL_Renderer* m_pSDLRenderer = nullptr;
        SDL_Window* m_pSDLWindow = nullptr;

        Log* m_pLog = nullptr;

    public:;
        void CreateGraphics (Log* log, SDL_Window* pWindow);
        void CloseGraphics();
        void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255);
        void Clear(int r = 255, int g = 255, int b = 255, int a = 255);
        void Present();
        void DrawImage(Image* pImage, int x = 0, int y = 0, Rect* pClip = nullptr, double angle = 0);
        SDL_Renderer* GetRender()
        {
            return m_pSDLRenderer;
        }
    };
}


