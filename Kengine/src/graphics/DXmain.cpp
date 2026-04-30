#include "Debugger.h"
#include "DXRenderer.h"
#include "DXWindow.h"
#include "engine/memory/AssetManager.h"
#include "engine/Timer.h"
#include "engine/physics/PhysicsManager.h"
#include "materials/DXMaterial_Lit.h"
#include "TechDemo/scripts/Player.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	// -----Initalising DirectX and Asset Manager-----
	DXWindow _dxWind{ 800, 600, hInstance, nCmdShow };
	DXRenderer _dxRend { _dxWind };
	AssetManager _AM{ _dxRend };

#pragma region Initialising Assets

	_AM.LoadAsset("Assets/cube.obj", "SampleMesh");
	_AM.LoadAsset("Assets/bust.obj", "Bust");
	_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");

#pragma endregion

#pragma region Initalising Materials

	DXMaterial material{ "Test", _dxRend, "src/Compiled Shaders/BaseVertexShader.cso","src/Compiled Shaders/BasePixelShader.cso", &_AM.GetTexture("SampleTexture") };

#pragma endregion

#pragma region Initalising Game Objects

	GameObject go_test{ "GO" , &_AM.GetMesh("SampleMesh"), &material, ColliderType::SPHERE, true, 2};
	RenderQueue::Instance()->AddObject(&go_test);

#pragma endregion

	// -----Player Initalisation-----
	Player player{ "Player", ColliderType::SPHERE, 2 };
	player.transform.Translate({ 0,0,10 });
	player.collider.UpdatePosition(player.transform);
	_dxRend.camera.SetParentObject(&player);

#pragma region DirectX MainLoop

	MSG msg;

	Debugging::OpenConsole();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else 
		{
			Timer::Update();

			auto kbState = DirectX::Keyboard::Get().GetState();

			auto msState = DirectX::Mouse::Get().GetState();
			_dxRend.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

			if (kbState.W)
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetForward() * player.moveSpeed * Timer::GetDeltaTime());
			if (kbState.A)
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());
			if (kbState.S)
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetForward() * player.moveSpeed * Timer::GetDeltaTime());
			if (kbState.D)
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());

			if (kbState.Escape)
			{
				PostQuitMessage(0);
			}

			player.Update();

			if (Collision::OnCollide(player.collider, go_test.collider)) 
				printf("Collision Occured");

			PhysicsManager::Instance()->UpdatePhysics(Timer::GetDeltaTime());

			_dxRend.RenderFrame();

		}
	}

	_dxRend.Release();

	return 0;

#pragma endregion

}
