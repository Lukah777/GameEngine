#include "Window.h"
#include "Log.h"
#include <iostream>
#include <SDL.h>

int Engine::Window::OpenWindow(Log* log, const char* WinName, int WinW, int WinH)
{
    // Asign log pointer
    m_pLog = log;


    // Call to SDL_Init(). This will initialize SDL and the video subsystem.
    int errorCode = SDL_Init(SDL_INIT_VIDEO);
    if (errorCode == 0)
    {
        // Print success message.
        m_pLog->PrintLog("SDL_Init() succeeded.");
    }
    else
    {
        // Print error message and quit.
        m_pLog->PrintLog("SDL_Init() failed. Error code ");
        m_pLog->PrintLog(std::to_string(errorCode));
        m_pLog->PrintLog(": ");
        m_pLog->PrintLog(SDL_GetError());
        system("pause");
        return errorCode;
    }

    // Attempt to create a window 
    m_pSDLWindow = SDL_CreateWindow(WinName,            // title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,    // x, y,
        WinW, WinH,                                        // w, h,
        SDL_WINDOW_RESIZABLE);                                                // flags
    if (m_pSDLWindow != nullptr)
    {
        // Print success message.
        m_pLog->PrintLog("SDL_CreateWindow() succeeded.");
    }
    else
    {
        // Print error message. Remember to quit SDL before exiting the program.
        m_pLog->PrintLog( "SDL_CreateWindow() failed. Error: ");
        m_pLog->PrintLog(SDL_GetError());
        SDL_Quit();
        system("pause");
        return -1;
    }
    return 0;
}

void Engine::Window::CloseWindow()
{
    SDL_DestroyWindow(m_pSDLWindow);
    SDL_Quit();
}
