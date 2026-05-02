#include "Player.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "engine/Timer.h"
#include "Weapon.h"

Player::Player(std::string name, std::string tag, ColliderType type, float circlerad)
	: GameObject(name, tag, nullptr, nullptr, type, true, circlerad)
{
}

/// <summary>
/// Update function, called every frame
/// </summary>
void Player::Update()
{
	collider.UpdatePosition(transform);
	//Gun->UpdateChildPosition();
}
