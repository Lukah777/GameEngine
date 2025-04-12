#pragma once
#include "../Engine/Log.h"
#include "../Engine/Window.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/MessageSystem.h"
#include <thread>

namespace Engine {
    class GameObject;

    class System
    {
    private:
        Log m_log;
        Window m_window;
        Graphics m_graphics;
        Input m_input;
        ResourceSystem m_resources;
        MessageSystem m_msgSys;
        int m_windowW;
        int m_windowH;
        int m_numCells;

        std::vector<GameObject*> m_GameObjects;

        std::thread m_worker;

    public:
        void Render(std::vector<GameObject*> pGameObjects);
        void Run();
        void Inialize(const char* windowName, int windowW, int windowH);
        void Deinitalize();
        Log* GetLog() {return &m_log;};
        Graphics* GetGraphics() { return &m_graphics; };
        Input* GetInput() { return &m_input; };
        ResourceSystem* GetResources() { return &m_resources; };
        MessageSystem* GetMessageSystem() { return &m_msgSys; };
        size_t GetGameObjectSize() { return m_GameObjects.size(); }
        GameObject* GetGameObjectAt(int index);
        void AddGameObject(GameObject* pGameObject) { m_GameObjects.emplace_back(pGameObject); };
        GameObject* GetBackGameObject() { return m_GameObjects.back(); };
        int GetWindowW() { return m_windowW; }
        int GetWindowH() { return m_windowH; }
        int GetNumCells() { return m_numCells; }
    };
}


