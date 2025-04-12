#pragma once
struct SDL_GetKeyboardState;

namespace Engine {
    class System;

    class Input
    {
    private:
        
    public:
        enum keycode {
            ENGINE_ESCAPE_KEY = 41,
            ENGINE_W_KEY = 26,
            ENGINE_A_KEY = 4,
            ENGINE_S_KEY = 22,
            ENGINE_D_KEY = 7,
            ENGINE_MOUSE_BUTTON = 1025,
            ENGINE_SPACE_KEY = 44
            
        };
        bool GetIsKeyDown(keycode key);
        bool Update(Engine::System* pSystem);
    };
}
