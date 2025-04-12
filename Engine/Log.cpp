#include <iostream>
#include "Log.h"

void Engine::Log::PrintLog(std::string string)
{
    std::cout << string << std::endl;
    m_LogFile << string;
}

void Engine::Log::OpenLog()
{
    m_LogFile.open("../Build/Log.txt");
}

void Engine::Log::CloseLog()
{
    m_LogFile.close();
}
