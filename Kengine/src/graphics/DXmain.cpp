#include "Debugger.h"
#include "DXRenderer.h"
#include "DXWindow.h"
#include "engine/gameobjects/GameObject.h"
#include "engine/gameobjects/DirectionalLightObject.h"
#include "engine/gameobjects/PointLightObject.h"
#include "engine/memory/AssetManager.h"
#include "engine/Timer.h"
#include "engine/physics/PhysicsManager.h"
#include "materials/DXMaterial_Transparent.h"
#include "TechDemo/scripts/Player.h"
#include "TechDemo/scripts/Weapon.h"

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

	// -----Meshes-----
	_AM.LoadAsset("Assets/cube.obj", "SampleMesh");
	_AM.LoadAsset("Assets/blaster-a.obj", "Gun");
	_AM.LoadAsset("Assets/bust.obj", "Bust");

	// -----Textures-----
	_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");
	_AM.LoadAsset("Assets/SkyBox.dds", "SkyBox");

#pragma endregion

#pragma region Initialise Lights

	XMVECTOR ambientLightColour{ 0.1f,0.1f,0.1f };
	RenderQueue::Instance()->ambientLightColour = ambientLightColour;
	DirectionalLightObject dirLight{ "DirectionalLight", XMVECTOR{0.9f, 1.0f, 1.0f}, DirectX::Colors::DeepPink};
	RenderQueue::Instance()->directionalLight = &dirLight;

	PointLightObject light1 { "PointLight1", DirectX::Colors::Aqua, 10};
	RenderQueue::Instance()->pointLights[0] = light1.pointLight;

#pragma endregion


#pragma region Initalising Materials

	// -----Unlit Materials-----
	DXMaterial material{ "BaseMaterial", _dxRend, "BaseVertexShader.cso","BasePixelShader.cso", &_AM.GetTexture("SampleTexture") };
	DXMaterial skyboxmaterial{ "SkyBoxMaterial", _dxRend, "SkyBoxVertexShader.cso","SkyBoxPixelShader.cso", &_AM.GetTexture("SkyBox") };

	// -----Lit Materials-----
	DXMaterial_Lit litmaterial{ "Base Lit Material", _dxRend, "LightVertexShader.cso","ReflectPixelShader.cso", &_AM.GetTexture("SampleTexture") };
	litmaterial.SetReflectionTexture(&_AM.GetTexture("SkyBox"));
	litmaterial.reflectiveness = 0.5f;

	// -----Transparent Materials-----
	//DXMaterial_Transparent transparentmat{ "Base Lit Material", _dxRend, "TransparentVertexShader.cso","TransparentPixelShader.cso", &_AM.GetTexture("SampleTexture") };
	//transparentmat.SetReflectionTexture(&_AM.GetTexture("SkyBox"));
	//transparentmat.transparency = 0.1f;

#pragma endregion

#pragma region Initalising Game Objects

	// ----SkyBox GO----
	GameObject go_skybox{ "SkyBoxGO", "SkyBox", & _AM.GetMesh("SampleMesh"), &skyboxmaterial, ColliderType::NONE, false };
	_dxRend.SkyBox = &go_skybox;

	// -----Gameplay GOs-----
	GameObject go_test{ "GO" , "Wall", & _AM.GetMesh("SampleMesh"), &litmaterial, ColliderType::SPHERE, true, 1};
	RenderQueue::Instance()->AddObject(&go_test);

	//GameObject go_bust{ "Head" , "Target", &_AM.GetMesh("Bust"), &material, ColliderType::SPHERE, false, 1 };
	//RenderQueue::Instance()->AddObject(&go_bust);


#pragma endregion

	// -----Player Initalisation-----
	Player player{ "Player", "Player", ColliderType::SPHERE, 1};
	player.transform.position = XMVectorSetZ(player.transform.position, -10);
	player.collider.UpdatePosition(player.transform);
	_dxRend.camera.SetParentObject(&player);
	_dxRend.camera.ray = { _dxRend.camera.transform, { 0, 0, 5 }, 1.5 };

	Weapon Gun{ "Gun" , &_AM.GetMesh("Gun"), &material, ColliderType::NONE };
	Gun.SetParent(&player);
	//RenderQueue::Instance()->AddObject(&Gun);
	player.Gun = &Gun;

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

#pragma region INPUT

			auto kbState = DirectX::Keyboard::Get().GetState();

			auto msState = DirectX::Mouse::Get().GetState();
			auto msTracker = Mouse::ButtonStateTracker();
			msTracker.Update(msState);

			_dxRend.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });
			player.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

			//printf("%.2f", XMVectorGetY(player.transform.rotation));

			if (kbState.W && !player.blockedforward)
			{
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetUnitForward() * player.moveSpeed * Timer::GetDeltaTime());
				player.transform.Translate(player.transform.GetUnitForward() * player.moveSpeed * Timer::GetDeltaTime());
				player.direction = CurrentDirection::Forward;

			}
			if (kbState.A && !player.blockedleft)
			{
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());
				player.transform.Translate(-player.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());
				player.direction = CurrentDirection::Left;

			}
			if (kbState.S && !player.blockedbackward)
			{
				_dxRend.camera.transform.Translate(-_dxRend.camera.transform.GetUnitForward() * player.moveSpeed * Timer::GetDeltaTime());
				player.transform.Translate(-player.transform.GetUnitForward() * player.moveSpeed * Timer::GetDeltaTime());
				player.direction = CurrentDirection::Backward;

			}
			if (kbState.D && !player.blockedright)
			{
				_dxRend.camera.transform.Translate(_dxRend.camera.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());
				player.transform.Translate(player.transform.GetRight() * player.moveSpeed * Timer::GetDeltaTime());
				player.direction = CurrentDirection::Right;
				
			}

			player.Update();
			_dxRend.camera.ray.UpdateValues(_dxRend.camera.transform);

			if (msTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
			{
				printf("Shots Fired!");
				Gun.Shoot();
			}

			if (kbState.Escape)
			{
				PostQuitMessage(0);
			}

#pragma endregion

			for (auto go : RenderQueue::Instance()->RenderableObjects)
			{
				if (Collision::OnCollide(&player, go))
				{
					if (go->Tag == "Wall")
					{
					switch (player.direction)
						{
						case CurrentDirection::Forward:
							player.blockedforward = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
							break;
						case CurrentDirection::Backward:
							player.blockedbackward = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
							break;
						case CurrentDirection::Right:
							player.blockedright = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
							break;
						case CurrentDirection::Left:
							player.blockedleft = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
							break;
						}
					}
					else
					{
						player.blockedforward = false;
						player.blockedbackward = false;
						player.blockedleft = false;
						player.blockedright = false;
					}
				}
				else
				{
					player.blockedforward = false;
					player.blockedbackward = false;
					player.blockedleft = false;
					player.blockedright = false;
				}
			}

			PhysicsManager::Instance()->UpdatePhysics(Timer::GetDeltaTime());

			_dxRend.RenderFrame();

		}
	}

	_dxRend.Release();

	return 0;

#pragma endregion

}
