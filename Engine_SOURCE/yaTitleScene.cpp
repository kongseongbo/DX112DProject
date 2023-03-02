#include "yaTitleScene.h"
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

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Grid Object
		GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
		MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridScript = gridObject->AddComponent<GridScript>();
		gridScript->SetCamera(cameraComp);

		// Map
		GameObject* mapObj = object::Instantiate<GameObject>(eLayerType::Map);
		mapObj->SetName(L"Mission1Map");
		Transform* map1Tr = mapObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(0.0f, 0.0f, 6.0f));
		map1Tr->SetScale(Vector3(20.0f, 15.0f, 1.0f));

		MeshRenderer* mapMr = mapObj->AddComponent<MeshRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mapMaterial = Resources::Find<Material>(L"Mission1Material");
		mapMr->SetMaterial(mapMaterial);
		mapMr->SetMesh(mesh);

		// MapBG
		GameObject* mapBGObj = object::Instantiate<GameObject>(eLayerType::BGMap);
		mapBGObj->SetName(L"Mission1BGMap");
		Transform* map1BGTr = mapBGObj->GetComponent<Transform>();
		map1BGTr->SetPosition(Vector3(0.0f, 0.0f, 6.0f));
		map1BGTr->SetScale(Vector3(20.0f, 15.0f, 1.0f));

		MeshRenderer* mapBGMr = mapBGObj->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mapBGMaterial = Resources::Find<Material>(L"Mission1BGMaterial");
		mapBGMr->SetMaterial(mapBGMaterial);
		mapBGMr->SetMesh(mesh);


		// Light Object
		GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
		spriteObj->SetName(L"LIGHT");
		Transform* spriteTr = spriteObj->GetComponent<Transform>();
		spriteTr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);


		//SMILE RECT
		GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player);
		obj->SetName(L"SMILE");
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(-3.0f, 0.0f, 5.0f));
		tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);
		obj->AddComponent<PlayerScript>();
		object::DontDestroyOnLoad(obj); 

		//SMILE RECT CHild
		GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
		child->SetName(L"SMILE");
		Transform* childTr = child->GetComponent<Transform>();
		childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		childTr->SetParent(tr);

		MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(mesh);

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
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}