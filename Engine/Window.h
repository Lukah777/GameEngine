#pragma once
struct SDL_Window;


namespace Engine
{
    class Log;
    class Window
    {
    private:
        const char* m_WinName = "Test Title";
        const int m_WinW = 1024;
        const int m_WinH = 768;

        // Pointer to the application window managed by SDL.
        SDL_Window* m_pSDLWindow = nullptr;

        Log* m_pLog = nullptr;

    public:
        int OpenWindow(Log* log, const char* WinName = "Test Title", int WinW = 1024, int WinH = 768);
        void CloseWindow();
        SDL_Window* GetSDLWindow() { return m_pSDLWindow; }
    };
}

