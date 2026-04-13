#include "Debugger.h"
#include "DXRenderer.h"
#include "DXWindow.h"
#include "DXMesh.h"
#include "engine/gameobjects/GameObject.h"
#include "DXTexture.h"
#include "DXMaterial.h"
#include "engine/memory/AssetManager.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	DXWindow _dxWind{ 800, 600, hInstance, nCmdShow };
	DXRenderer _dxRend{ _dxWind };
	AssetManager _AM{ _dxRend };

	//DXMesh mesh{ _dxRend, "Assets/cube.obj" };
	//DXTexture tex{ _dxRend, "Assets/SampleTexture.jpg" };
	//DXMaterial material{ "Test",_dxRend,"src/Compiled Shaders/BaseVertexShader.cso","src/Compiled Shaders/BasePixelShader.cso", &tex };

	//GameObject go_test { "GO" , &mesh, &material};

	//_dxRend.testGO = &go_test;

	_AM.LoadAsset("Assets/cube.obj", "SampleMesh");
	_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");
	DXMaterial material{ "Test",_dxRend,"src/Compiled Shaders/BaseVertexShader.cso","src/Compiled Shaders/BasePixelShader.cso", _AM.GetTexture("SampleTexture")};

	GameObject go_test { "GO" , _AM.GetMesh("SampleMesh"), &material};

	_dxRend.testGO = &go_test;

	_dxRend.camera.transform.position = DirectX::XMVectorSetZ(_dxRend.camera.transform.position, -10);

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
			auto kbState = DirectX::Keyboard::Get().GetState();

			auto msState = DirectX::Mouse::Get().GetState();
			_dxRend.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

			if (kbState.W)
				_dxRend.camera.transform.Translate(DirectX::XMVectorScale(_dxRend.camera.transform.GetForward(), 0.01f));
			if (kbState.A)
				_dxRend.camera.transform.Translate(DirectX::XMVectorScale(_dxRend.camera.transform.GetRight(), -0.01f));
			if (kbState.S)
				_dxRend.camera.transform.Translate(DirectX::XMVectorScale(_dxRend.camera.transform.GetForward(), -0.01f));
			if (kbState.D)
				_dxRend.camera.transform.Translate(DirectX::XMVectorScale(_dxRend.camera.transform.GetRight(), 0.01f));
			if (kbState.Q)
				_dxRend.camera.transform.Translate({ 0, 0.01f, 0 });
			if (kbState.E)
				_dxRend.camera.transform.Translate({ 0, -0.01f, 0 });

			if (kbState.Escape)
			{
				PostQuitMessage(0);
			}

			if (msState.leftButton) _dxRend.camera.transform.position = { 0, 0, -5 };
			if (msState.rightButton) _dxRend.camera.transform.position = { 0, 0, 5 };


			_dxRend.RenderFrame();

		}
	}

	_dxRend.Release();

	return 0;
}
