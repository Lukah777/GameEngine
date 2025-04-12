#pragma once
#include <unordered_map>
#include "Unzipper.h"
#include "Image.h"  
#include "../Engine/TinyXMLParser.h"
#include "TMXParser.h"
#include <string>
struct SDL_Renderer;

namespace Engine 
{
    class Log;
    class Image;
    class ResourceSystem
    {
    private:
        Log* m_pLog = nullptr;
        Unzipper m_unzipper;
        std::unordered_map<std::string, Image*> m_ImageMap;
        TinyXMLParser m_XMLparser;
        TMXParser m_TMXparser;

    public:
        void CloseResourceSystem();
        void CreateResources(Log* plog, System* pSystem, std::string file);
        Image* GetImageData(const char* fileName, SDL_Renderer* pSDLRenderer);
        TMXParser* GetTMXParser() { return &m_TMXparser; };
        void RunLuaScript(std::string fileName);
    };
}
