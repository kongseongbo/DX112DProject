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
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"


namespace ya
{
	Stage1Scene::Stage1Scene()
		: Scene(eSceneType::Stage1)
	{

	}

	Stage1Scene::~Stage1Scene()
	{
	}

	void Stage1Scene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
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

		//Player
		Player* headObj = object::Instantiate<Player>(eLayerType::Player, this);
		headObj->SetName(L"Head");
		Transform* headTr = headObj->GetComponent<Transform>();
		headTr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		headTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));		
		headObj->AddComponent<Animator>();
		PlayerScript* playerscript = headObj->AddComponent<PlayerScript>();
		playerscript->SetHeadAnimator(headObj->GetComponent<Animator>());
		playerscript->SetHeadPlayer(headObj);

		SpriteRenderer* headMr = headObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> headMateiral = Resources::Find<Material>(L"SpriteMaterial");
		headMr->SetMaterial(headMateiral);
		headMr->SetMesh(mesh);
		object::DontDestroyOnLoad(headObj);

		Player* bodyObj = object::Instantiate<Player>(eLayerType::Body, this);
		bodyObj->SetName(L"Body");
		Transform* bodyTr = bodyObj->GetComponent<Transform>();
		bodyTr->SetPosition(Vector3(headTr->GetPosition().x - 0.15f, headTr->GetPosition().y - 1.0f, 5.0f));
		bodyTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		bodyObj->AddComponent<Animator>();
		bodyObj->AddComponent<PlayerScript>();
		playerscript->SetBodyAnimator(bodyObj->GetComponent<Animator>());
		playerscript->SetBodyPlayer(bodyObj);

		Collider2D* collider = bodyObj->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetCenter(Vector2(0.0f, -0.1f));
		collider->SetSize(Vector2(0.2f, 0.2f));
		/*Animator* animator = obj->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Character\\Marco\\IdleU.png");
		animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 36.0f), Vector2::Zero, 4, 0.3f);
		animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
		animator->Play(L"HeadIdle", true);*/

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
		std::shared_ptr<Material> monsterMateiral = Resources::Find<Material>(L"RectMaterial");
		monsterMr->SetMaterial(monsterMateiral);
		monsterMr->SetMesh(mesh);

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
		fadeTr->SetPosition(Vector3(0.0f, 0.0f, 4.0f));
		MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
		fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		fadeObject->AddComponent<FadeInOutScript>();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initalize();
	}

	void Stage1Scene::Update()
	{
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
