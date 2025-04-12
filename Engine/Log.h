#pragma once
#include <string>
#include <fstream>

namespace Engine
{
    class Log
    {
    private:
        std::fstream m_LogFile;
        
    public:
        void PrintLog(std::string string);
        void OpenLog();
        void CloseLog();
       
    };
    
}