#include "MessageSystem.h"
#include "GameObject.h"
#include "System.h"

void Engine::MessageSystem::SendMsg(const char* msg, Engine::GameObject* pSender, Engine::GameObject* pRecipiant)
{
    m_messages.push_back(Message(msg, pSender, pRecipiant));
}

void Engine::MessageSystem::DistributeMsgs(System* pSystem)
{
    for (int i = 0; i < m_messages.size(); i++)
    {
        for (int j = 0; j < pSystem->GetGameObjectSize(); j++)
        {
            pSystem->GetGameObjectAt(j)->PassMsg(m_messages.at(i));
        }
    }
    m_messages.clear();
}