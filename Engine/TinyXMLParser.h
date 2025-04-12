#pragma once
#include <vector>
#include <string>

namespace Engine
{
    class System;
    class TinyXMLParser
    {
    public:
        void RunParser(System* pSystem, std::string file);
    };
}

