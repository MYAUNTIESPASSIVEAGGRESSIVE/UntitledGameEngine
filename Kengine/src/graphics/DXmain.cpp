#include "Debugger.h"
#include "DXRenderer.h"
#include "DXWindow.h"
#include "engine/memory/AssetManager.h"
#include "engine/Timer.h"
#include "engine/physics/PhysicsManager.h"
#include "materials/DXMaterial_Lit.h"
#include "TechDemo/scripts/Player.h"
#include "TechDemo/Level.h"
	

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	DXWindow _dxWind{ 800, 600, hInstance, nCmdShow };
	DXRenderer _dxRend { _dxWind };
	AssetManager _AM{ _dxRend };
	Level _level { _dxRend, _AM };

	//_AM.LoadAsset("Assets/cube.obj", "SampleMesh");
	//_AM.LoadAsset("Assets/bust.obj", "Bust");
	//_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");
	//DXMaterial material{ "Test", _dxRend, "src/Compiled Shaders/BaseVertexShader.cso","src/Compiled Shaders/BasePixelShader.cso", &_AM.GetTexture("SampleTexture") };

	//GameObject go_test{ "GO" , &_AM.GetMesh("SampleMesh"), &material, ColliderType::BOX, true };

	//_dxRend.renderQueue.AddObject(&go_test);

	_level.InitLevel();
	LOG("initialised Level");

	Player player{ "Player", ColliderType::BOX, _dxRend.camera };

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
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetForward() * 10 * Timer::GetDeltaTime());
			if (kbState.A)
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetRight() * 10 * Timer::GetDeltaTime());
			if (kbState.S)
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetForward() * 10 * Timer::GetDeltaTime());
			if (kbState.D)
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetRight() * 10 * Timer::GetDeltaTime());

			if (kbState.Escape)
			{
				PostQuitMessage(0);
			}

			player.Update();

			PhysicsManager::Instance()->UpdatePhysics(Timer::GetDeltaTime());

			_dxRend.RenderFrame();

		}
	}

	_dxRend.Release();

	return 0;
}
