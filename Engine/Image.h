#pragma once
struct SDL_Texture;
struct SDL_Rect;

namespace Engine
{
    class Image
    {
    private:
        SDL_Texture* m_pTexture = nullptr;
        int m_width = 0;
        int m_height = 0;
    public:
        Image() {};
        Image(SDL_Texture* pTexture, int width, int height);
        ~Image();
        SDL_Texture* GetSDLTexture() { return m_pTexture; }
        int GetW() { return m_width; };
        int GetH() { return m_height; };
    };
}
