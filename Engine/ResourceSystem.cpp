#include "ResourceSystem.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Log.h"
#include "Image.h"
#include <string>
#include "../Lua/src/lua.hpp"
#include "../BLD/BleachNew.h"

void Engine::ResourceSystem::CloseResourceSystem()
{
    m_unzipper.CloseUnzipper();
    for (auto [key, val] : m_ImageMap)
    {
        BLEACH_DELETE(val);
    }
}

void Engine::ResourceSystem::CreateResources(Log* plog, System* pSystem, std::string file)
{
    m_pLog = plog;
#if NDEBUG
    m_unzipper.Unzip();
    m_XMLparser.RunParser(pSystem, m_unzipper.GetUnzippedXML(file));
    m_TMXparser.RunParser(pSystem, m_unzipper.GetUnzippedTMX("../Assets/SimpleMap.tmx"));

#else
    m_XMLparser.RunParser(pSystem, file);
    m_TMXparser.RunParser(pSystem, "../assets/SimpleMap.tmx"); 
#endif
};

Engine::Image* Engine::ResourceSystem::GetImageData(const char* fileName, SDL_Renderer* pSDLRenderer)
{
#if NDEBUG
    // Release
    std::string strFileName = fileName;
    if (m_ImageMap.find(strFileName) == m_ImageMap.end())
    {
        SDL_Surface* pImageSurface = m_unzipper.GetUnzippedImgs(strFileName);
        if (pImageSurface == NULL)
        {
            m_pLog->PrintLog("Failed to load image. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }
        SDL_Texture* pTextureTemp = SDL_CreateTextureFromSurface(pSDLRenderer, pImageSurface);

        if (pTextureTemp == NULL)
        {
            m_pLog->PrintLog("Failed to load texture. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }

        m_ImageMap.emplace(fileName, BLEACH_NEW(Image(pTextureTemp, pImageSurface->w, pImageSurface->h)));

        SDL_FreeSurface(pImageSurface);
        return m_ImageMap[strFileName];
    }
    else
    {
        return m_ImageMap[strFileName];
    }
#else
    // Debug

    std::string strFileName = "../";
    strFileName += fileName;
    const char* fullFileName = strFileName.c_str();
    if (m_ImageMap.find(fullFileName) == m_ImageMap.end())
    {
        // Create
        SDL_Surface* pImageSurface = IMG_Load(fullFileName);
        if (pImageSurface == NULL)
        {
            m_pLog->PrintLog("Failed to load image. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }
        SDL_Texture* pTextureTemp = SDL_CreateTextureFromSurface(pSDLRenderer, pImageSurface);


        if (pTextureTemp == NULL)
        {
            m_pLog->PrintLog("Failed to load texture. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }

        m_ImageMap.emplace(fullFileName, BLEACH_NEW(Image(pTextureTemp, pImageSurface->w, pImageSurface->h)));

        SDL_FreeSurface(pImageSurface);
        return m_ImageMap[fullFileName];
    }
    else
    {
        return m_ImageMap[fullFileName];
    }
#endif
    return nullptr;
}

void Engine::ResourceSystem::RunLuaScript(std::string file)
{
    lua_State* pLuaState = luaL_newstate();
    luaL_openlibs(pLuaState);

    luaL_dostring(pLuaState, "print('Hello, Lua!');");

#if NDEBUG
    luaL_dofile(pLuaState, m_unzipper.GetUnzippedLua(file).c_str());
#else
    luaL_dofile(pLuaState, file.c_str());
#endif
    lua_close(pLuaState);
}
