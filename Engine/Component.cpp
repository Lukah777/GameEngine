#include "Component.h"
#include "GameObject.h"

Engine::Component::Component(System* pSystem, GameObject* pGameObject)
{
    m_pMsgSys = pSystem->GetMessageSystem();
    m_Owner = pGameObject;
}

bool Engine::Component::Update(System*)
{
    return true;
}

void Engine::Component::Render(System*)
{
}

void Engine::Component::HandleMessage(Message)
{
}

Engine::GameObject* Engine::Component::GetOwner()
{
    return m_Owner;
}
