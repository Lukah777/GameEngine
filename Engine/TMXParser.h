#pragma once
#include <string>
#include <vector>


namespace Engine
{
    class Image;
    class System;
    class TMXParser
    {
        std::vector<int> m_backgroundVect;
        int m_width;
        int m_height;
        int m_tileWidth;
        int m_tileHeight;
    public:
        void RunParser(System* pSystem, std::string file);
        int GetBackgroundAtIndex(int index) { return m_backgroundVect[index]; }
        int GetWidth() { return m_width; };
        int GetHeight() { return m_height; };
        int GetSizeOfSprites() { return m_tileWidth; };
    };
};

