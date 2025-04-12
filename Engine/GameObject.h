#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"

namespace Engine
{
    class GameObject
    {
    private:
        MessageSystem* m_pMsgSys;
        std::unordered_map<std::string, Component*> m_components;
    public:

        GameObject(MessageSystem* pMsgSys);
        ~GameObject();
        void AddComponent(std::string compName, Component* pComponent);
        Component* GetComponent(std::string compName);
        bool Update(System* pSystem);
        void Render(Engine::System* pSystem);
        void PassMsg(Engine::Message msg);
    };
}


