#include "EnemyComponent.h"
#include "GameObject.h"

Engine::EnemyComponent::EnemyComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}
