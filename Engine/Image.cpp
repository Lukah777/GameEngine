#include "Image.h"
#include <SDL_image.h>

Engine::Image::Image(SDL_Texture* pTexture, int width, int height)
{
    m_pTexture = pTexture;
    m_width = width;
    m_height = height;
}

Engine::Image::~Image()
{
    SDL_DestroyTexture(m_pTexture);
}
