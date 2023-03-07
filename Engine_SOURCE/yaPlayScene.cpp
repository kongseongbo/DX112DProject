#include "yaPlayScene.h"
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

namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		
		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Map
		GameObject* mapObj = object::Instantiate<GameObject>(eLayerType::Map);
		mapObj->SetName(L"Mission1Map");
		Transform* map1Tr = mapObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(0.0f, 0.0f, 6.0f));
		map1Tr->SetScale(Vector3(20.0f, 15.0f, 1.0f));

		MeshRenderer* mapMr = mapObj->AddComponent<MeshRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mapMaterial = Resources::Find<Material>(L"MapMaterial");
		mapMr->SetMaterial(mapMaterial);
		mapMr->SetMesh(mesh);

		// Light Object
		//GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
		//spriteObj->SetName(L"LIGHT");
		//Transform* spriteTr = spriteObj->GetComponent<Transform>();
		//spriteTr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		//

		//SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
		////std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		//sr->SetMaterial(spriteMaterial);
		//sr->SetMesh(mesh);


		//SMILE RECT
		Player* obj = object::Instantiate<Player>(eLayerType::Player);
		obj->SetName(L"SMILE");
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//Collider2D* collider = obj->AddComponent<Collider2D>();
		//collider->SetType(eColliderType::Rect);
		//collider->SetCenter(Vector2(0.2f, 0.2f));
		//collider->SetSize(Vector2(1.5f, 1.5f));

		MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
		mr->SetMaterial(mateiral);
		//std::shared_ptr<Mesh> smileMesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
		obj->AddComponent<PlayerScript>();
		object::DontDestroyOnLoad(obj);

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
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
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
		GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::FadeIn);
		Transform* fadeTr = fadeObject->GetComponent<Transform>();
		fadeTr->SetPosition(Vector3(0.0f, 0.0f, 4.0f));
		MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
		fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		fadeObject->AddComponent<FadeInOutScript>();

		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{

	}

	void PlayScene::OnExit()
	{

	}

}
