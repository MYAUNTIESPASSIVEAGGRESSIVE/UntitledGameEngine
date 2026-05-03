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
#include "TechDemo/scripts/Target.h"

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
	_AM.LoadAsset("Assets/bust.obj", "HeadBust");
	_AM.LoadAsset("Assets/Floor.obj", "Floor");
	_AM.LoadAsset("Assets/target.obj", "Target");

	// -----Textures-----
	_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");
	_AM.LoadAsset("Assets/metal.png", "MetalTexture");
	_AM.LoadAsset("Assets/rock4.png", "RockTexture");
	_AM.LoadAsset("Assets/grass.png", "GrassTexture");
	_AM.LoadAsset("Assets/blocks1.jpg", "WallTexture");
	_AM.LoadAsset("Assets/SkyBox.dds", "SkyBox");

#pragma endregion

#pragma region Initialise Lights

	// ---- Ambient and Directional Lighting ----
	XMVECTOR ambientLightColour{ 0.3f,0.3f,0.3f };
	RenderQueue::Instance()->ambientLightColour = ambientLightColour;
	DirectionalLightObject dirLight{ "DirectionalLight", XMVECTOR{0.3f, 10.0f, 1.0f}, DirectX::Colors::AliceBlue};
	RenderQueue::Instance()->directionalLight = &dirLight;

	// ---- Point Lights ----
	PointLightObject light1 { "PointLight1", DirectX::Colors::Aqua, 50};
	light1.transform.position = XMVectorSet(-23, 5, -20, 1);
	light1.transform.rotation = XMVectorSet(3, 0, 0, 1);
	RenderQueue::Instance()->pointLights[0] = light1.pointLight;

	PointLightObject light2{ "PointLight1", DirectX::Colors::Red, 50 };
	light2.transform.position = XMVectorSet(-23, 5, 0, 1);
	light2.transform.rotation = XMVectorSet(3, 0, 0, 1);
	RenderQueue::Instance()->pointLights[0] = light2.pointLight;

	PointLightObject light3{ "PointLight1", DirectX::Colors::Green, 50 };
	light3.transform.position = XMVectorSet(-23, 5, 20, 1);
	light3.transform.rotation = XMVectorSet(3, 0, 0, 1);
	RenderQueue::Instance()->pointLights[0] = light3.pointLight;

#pragma endregion


#pragma region Initalising Materials
	// Unfortunately there should be a material per texture (to be updated)

	// -----Unlit Materials-----
	DXMaterial material{ "BaseMaterial", _dxRend, "BaseVertexShader.cso","BasePixelShader.cso", &_AM.GetTexture("SampleTexture") };
	DXMaterial skyboxmaterial{ "SkyBoxMaterial", _dxRend, "SkyBoxVertexShader.cso","SkyBoxPixelShader.cso", &_AM.GetTexture("SkyBox") };

	// -----Lit Materials-----

	DXMaterial_Lit litmaterial{ "Base Lit Material", _dxRend, "LightVertexShader.cso","ReflectPixelShader.cso", &_AM.GetTexture("WallTexture") };
	litmaterial.SetReflectionTexture(&_AM.GetTexture("SkyBox"));
	litmaterial.reflectiveness = 0.5f;

	DXMaterial_Lit grasslitmaterial{ "Floor Lit Material", _dxRend, "LightVertexShader.cso","ReflectPixelShader.cso", &_AM.GetTexture("RockTexture") };
	grasslitmaterial.SetReflectionTexture(&_AM.GetTexture("SkyBox"));
	grasslitmaterial.reflectiveness = 0.5f;


	DXMaterial_Lit metallitmaterial{ "Metal Lit Material", _dxRend, "LightVertexShader.cso","ReflectPixelShader.cso", &_AM.GetTexture("MetalTexture") };
	metallitmaterial.SetReflectionTexture(&_AM.GetTexture("SkyBox"));
	metallitmaterial.reflectiveness = 0.2f;

#pragma endregion

#pragma region Initalising Game Objects

	// Transparent/Clipped textures should be constructed and added first

	// -----SkyBox GO-----
	GameObject go_skybox{ "SkyBoxGO", "SkyBox", & _AM.GetMesh("SampleMesh"), &skyboxmaterial, ColliderType::NONE, false };
	_dxRend.SkyBox = &go_skybox;

	// -----Scene GOs-----

	GameObject go_floor{ "FloorGO" , "Floor", &_AM.GetMesh("Floor"), &grasslitmaterial, ColliderType::NONE, false, 0 };
	RenderQueue::Instance()->AddObject(&go_floor);
	go_floor.transform.scale = { 0.05f,0.05f,0.05f };
	go_floor.transform.position = XMVectorSet(0, -1, -40, 1);

	// -----Gameplay GOs-----

	// ----- Walls -----
	GameObject go_wall{ "GO" , "Wall", & _AM.GetMesh("SampleMesh"), &litmaterial, ColliderType::BOX, false, 1};
	RenderQueue::Instance()->AddObject(&go_wall);
	go_wall.transform.scale = { 1,10,10 };
	go_wall.transform.position = XMVectorSet(-30, 0, -20, 1);
	go_wall.collider.UpdatePosition(go_wall.transform);

	GameObject go_wall2{ go_wall };
	RenderQueue::Instance()->AddObject(&go_wall2);
	go_wall2.transform.scale = { 1,10,10 };
	go_wall2.transform.position = XMVectorSet(-30, 0, 0, 1);
	go_wall2.collider.UpdatePosition(go_wall2.transform);

	GameObject go_wall3{ go_wall };
	RenderQueue::Instance()->AddObject(&go_wall3);
	go_wall3.transform.scale = { 1,10,10 };
	go_wall3.transform.position = XMVectorSet(-30, 0, 20, 1);
	go_wall3.collider.UpdatePosition(go_wall3.transform);

	GameObject go_wall4{ go_wall };
	RenderQueue::Instance()->AddObject(&go_wall4);
	go_wall4.transform.scale = { 1,10,10 };
	go_wall4.transform.position = XMVectorSet(-30, 20, 0, 1);
	go_wall4.collider.UpdatePosition(go_wall4.transform);

	GameObject go_wall5{ go_wall };
	RenderQueue::Instance()->AddObject(&go_wall5);
	go_wall5.transform.scale = { 1,10,10 };
	go_wall5.transform.position = XMVectorSet(-30, 20, 20, 1);
	go_wall5.collider.UpdatePosition(go_wall5.transform);

	GameObject go_wall6{ go_wall };
	RenderQueue::Instance()->AddObject(&go_wall6);
	go_wall6.transform.scale = { 1,10,10 };
	go_wall6.transform.position = XMVectorSet(-30, 20, -20, 1);
	go_wall6.collider.UpdatePosition(go_wall6.transform);

	// ----- Targets -----
	Target go_target{ "Head" , "Target", &_AM.GetMesh("Target"), &metallitmaterial, ColliderType::SPHERE, false, 1 };
	RenderQueue::Instance()->AddObject(&go_target);
	go_target.transform.position = XMVectorSet(-25, -2, -20, 1);
	go_target.transform.scale = { 5, 5, 5 };
	go_target.transform.rotation = { 0, 1.5, 0 };
	go_target.collider.UpdatePosition(go_target.transform);

	Target go_target2{ go_target };
	RenderQueue::Instance()->AddObject(&go_target2);
	go_target2.transform.position = XMVectorSet(-25, -2, 0, 1);
	go_target2.transform.scale = { 5, 5, 5 };
	go_target2.transform.rotation = { 0, 1.5, 0 };
	go_target2.collider.UpdatePosition(go_target2.transform);

	Target go_target3{ go_target };
	RenderQueue::Instance()->AddObject(&go_target3);
	go_target3.transform.position = XMVectorSet(-25, -2, 20, 1);
	go_target3.transform.scale = { 5, 5, 5 };
	go_target3.transform.rotation = { 0, 1.5, 0 };
	go_target3.collider.UpdatePosition(go_target3.transform);

	// ----- Other -----

	GameObject go_collider{ "Collision Tester" , "Wall", &_AM.GetMesh("SampleMesh"), &litmaterial, ColliderType::SPHERE, true, 1 };
	RenderQueue::Instance()->AddObject(&go_collider);
	go_collider.collider.UpdatePosition(go_collider.transform);

	GameObject go_collider2{ go_collider };
	RenderQueue::Instance()->AddObject(&go_collider2);
	go_collider2.transform.position = XMVectorSet(30, 50, 0, 1);
	go_collider2.Mass = 100;
	go_collider2.collider.UpdatePosition(go_collider2.transform);

#pragma endregion

	// -----Player Initalisation-----
	Player player{ "Player", "Player", ColliderType::SPHERE, 1};
	player.transform.position = XMVectorSetZ(player.transform.position, -10);
	player.collider.UpdatePosition(player.transform);
	_dxRend.camera.SetParentObject(&player);
	_dxRend.camera.ray = { _dxRend.camera.transform, { 0, 0, 5 }, 0.2f };

	Weapon Gun{ "Gun" , &_AM.GetMesh("Gun"), &metallitmaterial, ColliderType::NONE };
	//Gun.transform.scale = { 0.1f,0.1f,0.1f };
	Gun.transform.position = XMVectorSet(5, 0, 0, 1);
	Gun.SetParent(&player);
	Gun.gunray = {Gun.transform,{ 0, 0, 5 }, 1.0f };
	RenderQueue::Instance()->AddObject(&Gun);
	player.Gun = &Gun;

	
#pragma region DirectX MainLoop

	MSG msg;

	Debugging::OpenConsole();

	// Main While loop of engine
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
			// updates the timer
			Timer::Update();

#pragma region INPUT

			auto kbState = DirectX::Keyboard::Get().GetState();
			auto kbsTracker = DirectX::Keyboard::KeyboardStateTracker();
			kbsTracker.Update(kbState);

			auto msState = DirectX::Mouse::Get().GetState();
			auto msTracker = Mouse::ButtonStateTracker();
			msTracker.Update(msState);

			_dxRend.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });
			player.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });
			player.GunHolder.Rotate({ (float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

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

#pragma region CollisionDetection

			for (auto go : RenderQueue::Instance()->RenderableObjects)
			{
				if (Collision::OnCollide(&player, go) && go->Tag == "Wall")
				{
					switch (player.direction)
					{
					case CurrentDirection::Forward:
						player.blockedforward = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
						player.collider.previousCollidedObject = go->Tag;
						break;
					case CurrentDirection::Backward:
						player.blockedbackward = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
						player.collider.previousCollidedObject = go->Tag;
						break;
					case CurrentDirection::Right:
						player.blockedright = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
						player.collider.previousCollidedObject = go->Tag;
						break;
					case CurrentDirection::Left:
						player.blockedleft = Collision::RayCastCheck(_dxRend.camera.ray, go->collider);
						player.collider.previousCollidedObject = go->Tag;
						break;
					}
				}
				else if (!Collision::OnCollide(&player, go) && go->Tag == "Wall" && player.collider.previousCollidedObject == "Wall")
				{
					player.blockedbackward = false;
					player.blockedforward = false;
					player.blockedright = false;
					player.blockedleft = false;

					go->velocity = { 0, 0, 0 };
				}
			}

#pragma endregion

			go_collider2.ApplyForce({ PhysicsManager::Instance()->Gravity * 20}, Timer::GetDeltaTime());

			PhysicsManager::Instance()->UpdatePhysics(Timer::GetDeltaTime());

			// do not remove
			_dxRend.RenderFrame();

		}
	}

	// do not remove
	_dxRend.Release();

	return 0;

#pragma endregion

}
