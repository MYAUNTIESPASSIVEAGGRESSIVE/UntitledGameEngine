#include "PhysicsManager.h"
PhysicsManager* PhysicsManager::_instance = NULL;

PhysicsManager* PhysicsManager::Instance()
{
    if (_instance == NULL) return _instance = new PhysicsManager();

    return _instance;
}
