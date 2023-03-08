#include "yaCharacterSelectScene.h"
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
#include "yaApplication.h"

extern ya::Application application;

namespace ya
{
	CharacterSelectScene::CharacterSelectScene()
		: Scene(eSceneType::CharacterSelect)
	{
	}
	CharacterSelectScene::~CharacterSelectScene()
	{
	}
	void CharacterSelectScene::Initalize()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left);
		float height = (winRect.bottom - winRect.top);

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		GameObject* selectObj = object::Instantiate<GameObject>(eLayerType::Map, this);
		selectObj->SetName(L"Select");
		Transform* map1Tr = selectObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
		map1Tr->SetScale(Vector3(width / 100.0f, height / 100.0f, 1.0f));

		SpriteRenderer* selectMr = selectObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> selectMaterial = Resources::Find<Material>(L"SelectMaterial");
		selectMr->SetMaterial(selectMaterial);
		selectMr->SetMesh(mesh);

		Scene::Initalize();
	}
	void CharacterSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void CharacterSelectScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void CharacterSelectScene::Render()
	{
		Scene::Render();
	}
	void CharacterSelectScene::OnEnter()
	{
	}
	void CharacterSelectScene::OnExit()
	{
	}
}