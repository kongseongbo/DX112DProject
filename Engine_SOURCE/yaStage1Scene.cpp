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

namespace ya
{
	Stage1Scene::Stage1Scene()
		: Scene(eSceneType::Stage1)
		, mHeadObj(nullptr)
		, mCameraObj(nullptr)
	{

	}

	Stage1Scene::~Stage1Scene()
	{
	}

	void Stage1Scene::Initalize()
	{
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
		mCameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = mCameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		CameraScript* cameraScript = mCameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Map
		GameObject* mapObj = object::Instantiate<GameObject>(eLayerType::Map, this);
		mapObj->SetName(L"Mission1Map");
		Transform* map1Tr = mapObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(1.0f, 1.0f, 10.0f));
		map1Tr->SetScale(Vector3(100.0f, 15.0f, 1.0f));

		SpriteRenderer* mapMr = mapObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mapMaterial = Resources::Find<Material>(L"MapMaterial");
		mapMr->SetMaterial(mapMaterial);
		mapMr->SetMesh(mesh);

		
		//Player Head
		mHeadObj = object::Instantiate<Player>(eLayerType::Player, this);
		mHeadObj->SetName(L"Head");
		Transform* headTr = mHeadObj->GetComponent<Transform>();
		headTr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		headTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
		//headTr->SetRotation(Vector3(0.0f, -180.0f, 0.0f));
		mHeadObj->AddComponent<Animator>();
		PlayerScript* playerscript = mHeadObj->AddComponent<PlayerScript>();
		playerscript->SetHeadAnimator(mHeadObj->GetComponent<Animator>());

		Collider2D* collider = mHeadObj->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetCenter(Vector2(0.0f, -0.6f));
		collider->SetSize(Vector2(0.2f, 0.2f));

		SpriteRenderer* headMr = mHeadObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> headMateiral = Resources::Find<Material>(L"SpriteMaterial");
		headMr->SetMaterial(headMateiral);
		headMr->SetMesh(mesh);
		object::DontDestroyOnLoad(mHeadObj);

		//Player Body
		Player* bodyObj = object::Instantiate<Player>(eLayerType::Body, this);
		bodyObj->SetName(L"Body");
		Transform* bodyTr = bodyObj->GetComponent<Transform>();
		bodyTr->SetPosition(Vector3(headTr->GetPosition().x - 0.2f, headTr->GetPosition().y - 1.3f, 5.0f));
		bodyTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
		bodyObj->AddComponent<Animator>();
		bodyObj->AddComponent<PlayerScript>();
		playerscript->SetBodyAnimator(bodyObj->GetComponent<Animator>());

		SpriteRenderer* bodyMr = bodyObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		bodyMr->SetMaterial(bodyMateiral);
		bodyMr->SetMesh(mesh);
		object::DontDestroyOnLoad(bodyObj);
		

		// Monster Object
		Monster* monsterObj = object::Instantiate<Monster>(eLayerType::Monster, this);
		monsterObj->SetName(L"Monster");
		Transform* monsterTr = monsterObj->GetComponent<Transform>();
		monsterTr->SetPosition(Vector3(3.0f, 0.0f, 5.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		Collider2D* monsterCollider = monsterObj->AddComponent<Collider2D>();
		monsterCollider->SetType(eColliderType::Rect);

		SpriteRenderer* monsterMr = monsterObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"smile", L"Smile.png");
		std::shared_ptr<Material> monsterMateiral = Resources::Find<Material>(L"SpriteMaterial");
		monsterMateiral->SetTexture(texture);
		monsterMr->SetMaterial(monsterMateiral);
		monsterMr->SetMesh(mesh);

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

		

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initalize();
	}

	void Stage1Scene::Update()
	{
		CameraScript* cameraScript = mCameraObj->GetComponent<CameraScript>();
		Transform* cameraTr = mCameraObj->GetComponent<Transform>();
		Transform* headTr = mHeadObj->GetComponent<Transform>();
		Vector3 headPos = headTr->GetPosition();
		cameraTr->SetPosition(headPos);

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