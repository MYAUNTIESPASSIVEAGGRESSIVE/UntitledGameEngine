#include "Player.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "engine/Timer.h"

Player::Player(std::string name, ColliderType type, Viewport cam)
	: GameObject(name, nullptr, nullptr, type, true)
{
	playercam = cam;
	playercam.SetParentObject(this);
}

/// <summary>
/// Update function, called every frame
/// </summary>
void Player::Update()
{

}

void Player::HandleInput()
{
	auto kbState = DirectX::Keyboard::Get().GetState();

	auto msState = DirectX::Mouse::Get().GetState();
	playercam.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

	if (kbState.W)
		transform.Translate(transform.GetForward() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.A)
		transform.Translate(-transform.GetRight() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.S)
		transform.Translate(-transform.GetForward() * moveSpeed * Timer::GetDeltaTime());
	if (kbState.D)
		transform.Translate(transform.GetRight() * moveSpeed * Timer::GetDeltaTime());
}
