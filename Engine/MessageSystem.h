#pragma once
#include <vector>

namespace Engine
{
    class GameObject;
    class System;
    struct Message
    {
        const char* m_msg;
        GameObject* m_pSender;
        GameObject* m_pRecipiant;
    };

    class MessageSystem
    {
    private:
        std::vector<Message> m_messages;
    public:
        void SendMsg(const char* msg, GameObject* pSender, GameObject* pRecipiant);
        void DistributeMsgs(System* pSystem);
    };
}

