#include "Player.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "engine/Timer.h"

Player::Player(std::string name, ColliderType type, float circlerad)
	: GameObject(name, nullptr, nullptr, type, true, circlerad)
{
}

/// <summary>
/// Update function, called every frame
/// </summary>
void Player::Update()
{
	HandleInput();
}

void Player::HandleInput()
{
	auto kbState = DirectX::Keyboard::Get().GetState();

	if (kbState.W)
		transform.Translate(transform.GetForward() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.A)
		transform.Translate(-transform.GetRight() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.S)
		transform.Translate(-transform.GetForward() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.D)
		transform.Translate(transform.GetRight() * moveSpeed * Timer::GetDeltaTime());

	collider.UpdatePosition(transform);
}
