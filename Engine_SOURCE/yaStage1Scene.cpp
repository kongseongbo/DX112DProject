#include "yaStage1Scene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaFadeInOutScript.h"
#include "yaCollider2D.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaLight.h"
#include "yaRigidbody.h"
#include "yaPaintShader.h"
#include "yaMapScript.h"
#include "yaHeadScript.h"
#include "yaBodyScript.h"
#include "yaParticleSystem.h"
#include "yaMachineGunScript.h"
#include "yaMachineGun.h"
#include "yaHelicopter.h"
#include "yaHelicopterScript.h"
#include "yaMosqueArtilleryScript.h"
#include "yaArabian.h"
#include "yaArabianScript.h"
#include "yaTime.h"
#include "yaParachute.h"
#include "yaParachuteScript.h"


namespace ya
{
	Stage1Scene::Stage1Scene()
		: Scene(eSceneType::Stage1)
		, mCameraObj(nullptr)
		, headObj(nullptr)
		, bodyObj(nullptr)
		, mTime(0.0f)
	{

	}

	Stage1Scene::~Stage1Scene()
	{
	}

	void Stage1Scene::Initalize()
	{
		//paint shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();

		// Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(5.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		// Main Camera
		{
			mCameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = mCameraObj->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* cameraScript = mCameraObj->AddComponent<CameraScript>();
			mainCamera = cameraComp;

			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
		
		// Map
		GameObject* mapObj = object::Instantiate<GameObject>(eLayerType::Map, this);
		mapObj->SetName(L"Mission1Map");
		Transform* map1Tr = mapObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(1.0f, 1.0f, 10.0f));
		map1Tr->SetScale(Vector3(180.0f, 18.0f, 1.0f));
		
		SpriteRenderer* mapMr = mapObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mapMaterial = Resources::Find<Material>(L"MapMaterial");
		mapMr->SetMaterial(mapMaterial);
		mapMr->SetMesh(mesh);

		// Map Collider
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::Map, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(1.0f, -5.0f, 1.0f));
			mapcolliderTr->SetScale(Vector3(180.0f, 1.5f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();
			
			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, -0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}

		// Collider
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::Collider, this);
			mapcolliderObj->SetName(L"Coll");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			mapcolliderTr->SetScale(Vector3(1.0f, 20.0f, 1.0f));
			MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(1.f, 1.f));
		}

		//
		GameObject* mosqueArtilleryObj = object::Instantiate<GameObject>(eLayerType::Map, this);
		mosqueArtilleryObj->SetName(L"MosqueArtillery");
		Transform* mosqueArtillery1Tr = mosqueArtilleryObj->GetComponent<Transform>();
		mosqueArtillery1Tr->SetPosition(Vector3(49.0f, -0.5f, 10.0f));
		mosqueArtillery1Tr->SetScale(Vector3(25.0f, 8.5f, 1.0f));
		mosqueArtilleryObj->AddComponent<MosqueArtilleryScript>();

		
		//Player Head
		{
			headObj = object::Instantiate<Player>(eLayerType::Player, this);
			headObj->SetName(L"Head");
			Transform* headTr = headObj->GetComponent<Transform>();
			headTr->SetPosition(Vector3(-10.0f, 2.0f, 5.0f));
			headTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			//headTr->SetRotation(Vector3(0.0f, -180.0f, 0.0f));
			headObj->AddComponent<Animator>();
			headObj->AddComponent<Rigidbody>();
			HeadScript* playerscript = headObj->AddComponent<HeadScript>();

			Collider2D* collider = headObj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetCenter(Vector2(-0.7f, -0.7f));
			collider->SetSize(Vector2(0.1f, 0.2f));

			SpriteRenderer* headMr = headObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> headMateiral = Resources::Find<Material>(L"SpriteMaterial");
			headMr->SetMaterial(headMateiral);
			headMr->SetMesh(mesh);
			object::DontDestroyOnLoad(headObj);
		
		//Player Body
			bodyObj = object::Instantiate<Body>(eLayerType::Body, this);
			bodyObj->SetName(L"Body");
			Transform* bodyTr = bodyObj->GetComponent<Transform>();
			bodyTr->SetPosition(Vector3(headTr->GetPosition().x - 0.2f, headTr->GetPosition().y - 1.3f, 5.0f));
			bodyTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			bodyObj->AddComponent<Animator>();
			BodyScript* bodyScript = bodyObj->AddComponent<BodyScript>();
			bodyScript->mHead = headObj;

			Collider2D* bodyCollider = bodyObj->AddComponent<Collider2D>();
			bodyCollider->SetType(eColliderType::Rect);
			bodyCollider->SetCenter(Vector2(-0.5f, -1.0f));
			bodyCollider->SetSize(Vector2(0.1f, 0.05f));

			SpriteRenderer* bodyMr = bodyObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
			bodyMr->SetMaterial(bodyMateiral);
			bodyMr->SetMesh(mesh);
			object::DontDestroyOnLoad(bodyObj);

			playerscript->SetBody(bodyObj);

		//parachute
			Parachute* parachute = object::Instantiate<Parachute>(eLayerType::Bullet, this);
			parachute->SetName(L"parachute");
			Transform* parachuteTr = parachute->GetComponent<Transform>();
			parachuteTr->SetPosition(Vector3(headTr->GetPosition().x , headTr->GetPosition().y, headTr->GetPosition().z));
			parachuteTr->SetScale(Vector3(10.0f, 10.0f, 1.0f)); 
			parachuteTr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			ParachuteScript* script = parachute->AddComponent<ParachuteScript>();
			script->SetPlayer(headObj);
		}

		// Monster Object
		Monster* monsterObj = object::Instantiate<Monster>(eLayerType::Monster, this);
		monsterObj->SetName(L"Monster");
		Transform* monsterTr = monsterObj->GetComponent<Transform>();
		monsterTr->SetPosition(Vector3(3.0f, -3.0f, 5.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		Collider2D* monsterCollider = monsterObj->AddComponent<Collider2D>();
		monsterCollider->SetType(eColliderType::Rect);

		SpriteRenderer* monsterMr = monsterObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> monsterMateiral = Resources::Find<Material>(L"RectMaterial");
		monsterMr->SetMaterial(monsterMateiral);
		monsterMr->SetMesh(mesh);

		// Helicopter Object
		Helicopter* heliObj = object::Instantiate<Helicopter>(eLayerType::Monster, this);
		heliObj->SetName(L"Helicopter");
		Transform* heliTr = heliObj->GetComponent<Transform>();
		heliTr->SetPosition(Vector3(3.0f, 5.0f, 5.0f));
		heliTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));

		heliObj->AddComponent<HelicopterScript>();

		


		// MachineGunItem
		MachineGun* machineGun = object::Instantiate<MachineGun>(eLayerType::MachineGunItem, this);
		machineGun->SetName(L"machineGun");
		Transform* machineGunTr = machineGun->GetComponent<Transform>();
		machineGunTr->SetPosition(Vector3(-5.0f, -4.0f, 2.0f));
		machineGunTr->SetScale(Vector3(10.0f, 10.0f,1.0f));
		MachineGunScript* machineGunScript = machineGun->AddComponent<MachineGunScript>();

		Collider2D* machineGunCollider = machineGun->AddComponent<Collider2D>();
		machineGunCollider->SetType(eColliderType::Rect);
		machineGunCollider->SetSize(Vector2(0.1f, 0.1f));

		Animator* machineGunAni = machineGun->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MachineGunItem", L"Bullet\\MachineGunItem.png");
		machineGunAni->Create(L"MachineGunItem", texture, Vector2(0.0f, 0.0f), Vector2(24.0f, 22.0f), Vector2::Zero, 2, 0.3f);

		SpriteRenderer* machineGunSr = machineGun->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> machineGunMateiral = Resources::Find<Material>(L"SpriteMaterial");
		machineGunSr->SetMaterial(machineGunMateiral);
		machineGunSr->SetMesh(mesh);
		machineGunAni->Play(L"MachineGunItem", true);

		// HPBAR
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI, this);
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = hpBar->GetComponent<Transform>();
		hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 6.0f));
		hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		hpBar->AddComponent(hpsr);
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		// FadeInOut
		GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::FadeIn, this);
		Transform* fadeTr = fadeObject->GetComponent<Transform>();
		fadeTr->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
		SpriteRenderer* fadeMr = fadeObject->AddComponent<SpriteRenderer>();
		fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		fadeObject->AddComponent<FadeInOutScript>();

		//Particle
		/*{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			obj->AddComponent<ParticleSystem>();
		}*/

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MachineGunItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::Map, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Collider, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::MonsterAttack, true);

		Scene::Initalize();
	}

	void Stage1Scene::Update()
	{
		CameraScript* cameraScript = mCameraObj->GetComponent<CameraScript>();
		Transform* cameraTr = mCameraObj->GetComponent<Transform>();
		if (headObj->GetState() == GameObject::Active)
		{
			Transform* headTr = headObj->GetComponent<Transform>();
			Vector3 headPos = headTr->GetPosition();
			cameraTr->SetPosition(Vector3(headPos.x, headPos.y + 3.0f, headPos.z));
			
		}

		
		if (headObj->GetState() == GameObject::Paused)
		{
			mTime += 2.0f * Time::DeltaTime();
			if (mTime >= 5.0f)
			{
				headObj->SetState(GameObject::Active);
				bodyObj->SetState(GameObject::Active);
				Transform* headTr = headObj->GetComponent<Transform>();
				Vector3 pos = headTr->GetPosition();
				pos.x -= 5.0f;
				headTr->SetPosition(pos);
				Animator* headAni = headObj->GetComponent<Animator>();
				headAni->Play(L"NewMarco", false);
				HeadScript* headScript = headObj->GetScript<HeadScript>();
				headScript->SetGunState(eGunState::GUN);

				mTime = 0.0f;
			}
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void Stage1Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Stage1Scene::Render()
	{
		Scene::Render();
	} 

	void Stage1Scene::OnEnter()
	{

	}

	void Stage1Scene::OnExit()
	{

	}

}



/*Animator* animator = obj->AddComponent<Animator>();
std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Character\\Marco\\IdleU.png");
animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 36.0f), Vector2::Zero, 4, 0.3f);
animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
animator->Play(L"HeadIdle", true);*/

//SMILE RECT CHild
/*GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
child->SetName(L"SMILE");
Transform* childTr = child->GetComponent<Transform>();
childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
childTr->SetParent(tr);

MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
childMr->SetMaterial(childmateiral);
childMr->SetMesh(mesh);*/