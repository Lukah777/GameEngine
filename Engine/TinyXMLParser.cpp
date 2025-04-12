#include "TinyXMLParser.h"
#include "../TinyXML/tinyxml2.h"
#include <string>
#include "../Engine/GameObject.h"
#include "../Engine/ImageComponent.h"
#include "../Engine/InputComponent.h"
#include "../Engine/PositionComponent.h"
#include "../Engine/TilingComponent.h"
#include "../Engine/PhysicsComponent.h"
#include "../Engine/CollisionComponent.h"
#include "../Engine/DoorComponent.h"
#include "../Engine/KeyComponent.h"
#include "../Engine/EnemyComponent.h"
#include "../Engine/DeathComponent.h"
#include "../Engine/HeroComponent.h"
#include "../BLD/BleachNew.h"
#include "AimingComponent.h"
#include "BulletComponent.h"
#include "AIComponent.h"
#include "EnemyBulletComponent.h"
#include "TeleporterComponent.h"

void Engine::TinyXMLParser::RunParser(System* pSystem, std::string file)
{
    
    tinyxml2::XMLDocument doc;

#if NDEBUG
    doc.Parse(file.c_str(), file.size());
#else
    doc.LoadFile(file.c_str());
#endif
    
    //tinyxml2::XMLElement* elementTag = doc.FirstChildElement("Level1");

    tinyxml2::XMLElement* entryTag = doc.FirstChildElement();

    while (entryTag != NULL)
    {
        std::string Name = entryTag->Name();
        if (Name != "GameObject")
        {
            entryTag = entryTag->NextSiblingElement();
            continue;
        }
        pSystem->AddGameObject(BLEACH_NEW(GameObject(pSystem->GetMessageSystem())));
        tinyxml2::XMLElement* componentTag = entryTag->FirstChildElement();

        while (componentTag != NULL)
        {
            GameObject* pGameObjectBack = pSystem->GetBackGameObject();
            std::string componentName = componentTag->Attribute("Name");
            if (componentName == "ImageComponent")
            {
                const char* fileName = componentTag->FirstChildElement()->GetText();
                pGameObjectBack->AddComponent("ImageComponent", BLEACH_NEW(Engine::ImageComponent(pSystem, pGameObjectBack, fileName)));
            }
            if (componentName == "PhysicsComponent")
            {
                pGameObjectBack->AddComponent("PhysicsComponent", BLEACH_NEW(Engine::PhysicsComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "InputComponent")
            {
                pGameObjectBack->AddComponent("InputComponent", BLEACH_NEW(Engine::InputComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "PositionComponent")
            {       
                int x = 0;
                int y = 0;
                double angle = 0.0;
                if (componentTag->FirstChildElement("X") != nullptr) //$ as a helper function? and cache result rather then looking up?
                {
                    std::string xStr = componentTag->FirstChildElement("X")->GetText();
                    x = stoi(xStr);
                }
                if (componentTag->FirstChildElement("Y") != nullptr)
                {
                    std::string yStr = componentTag->FirstChildElement("Y")->GetText();
                    y = stoi(yStr);
                }
                if (componentTag->FirstChildElement("Angle") != nullptr)
                {
                    std::string yStr = componentTag->FirstChildElement("Angle")->GetText();
                    angle = stoi(yStr);
                }
                pGameObjectBack->AddComponent("PositionComponent",  BLEACH_NEW(Engine::PositionComponent(pSystem, pGameObjectBack, x, y, angle)));
            }
            if (componentName == "TilingComponent")
            {
                const char* fileName = componentTag->FirstChildElement()->GetText();
                pGameObjectBack->AddComponent("TilingComponent", BLEACH_NEW(Engine::TilingComponent(pSystem, pGameObjectBack, fileName)));
            }
            if (componentName == "CollisionComponent")
            {
                pGameObjectBack->AddComponent("CollisionComponent", BLEACH_NEW(Engine::CollisionComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "DeathComponent")
            {
                pGameObjectBack->AddComponent("DeathComponent", BLEACH_NEW(Engine::DeathComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "HeroComponent")
            {
                pGameObjectBack->AddComponent("HeroComponent", BLEACH_NEW(Engine::HeroComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "DoorComponent")
            {
                pGameObjectBack->AddComponent("DoorComponent", BLEACH_NEW(Engine::DoorComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "KeyComponent")
            {
                pGameObjectBack->AddComponent("KeyComponent", BLEACH_NEW(Engine::KeyComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "EnemyComponent")
            {
                pGameObjectBack->AddComponent("EnemyComponent", BLEACH_NEW(Engine::EnemyComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "AimingComponent")
            {
                pGameObjectBack->AddComponent("AimingComponent", BLEACH_NEW(Engine::AimingComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "BulletComponent")
            {
                pGameObjectBack->AddComponent("BulletComponent", BLEACH_NEW(Engine::BulletComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "EnemyBulletComponent")
            {
                pGameObjectBack->AddComponent("EnemyBulletComponent", BLEACH_NEW(Engine::EnemyBulletComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "AIComponent")
            {
                pGameObjectBack->AddComponent("AIComponent", BLEACH_NEW(Engine::AIComponent(pSystem, pGameObjectBack)));
            }
            if (componentName == "TeleporterComponent")
            {
                pGameObjectBack->AddComponent("TeleporterComponent", BLEACH_NEW(Engine::TeleporterComponent(pSystem, pGameObjectBack)));
            }
            componentTag = componentTag->NextSiblingElement();
        }
        entryTag = entryTag->NextSiblingElement();
    }
}
