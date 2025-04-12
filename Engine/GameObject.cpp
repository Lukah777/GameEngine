#include "GameObject.h"
#include "../BLD/BleachNew.h"

Engine::GameObject::GameObject(MessageSystem* pMsgSys)
{
    m_pMsgSys = pMsgSys;
}

Engine::GameObject::~GameObject()
{
    for (auto [key, comp] : m_components)
    {
        BLEACH_DELETE(comp);
    }
}

void Engine::GameObject::AddComponent(std::string compName, Component* pComponent)
{
    m_components.emplace(compName, pComponent);
}

Engine::Component* Engine::GameObject::GetComponent(std::string compName)
{
    if (m_components.find(compName) != m_components.end())
        return m_components.at(compName);
    else
        return nullptr;
}

bool Engine::GameObject::Update(System* pSystem)
{
    for (const auto& [key, value] : m_components)
    {
        if (!value->Update(pSystem))
            return false;
    }
    return true;
}

void Engine::GameObject::Render(Engine::System* pSystem)
{
    for (const auto& [key, value] : m_components)
    {
        value->Render(pSystem);
    }
}

void Engine::GameObject::PassMsg(Engine::Message msg)
{
    for (auto comp : m_components)
    {
        comp.second->HandleMessage(msg);
    }
}
