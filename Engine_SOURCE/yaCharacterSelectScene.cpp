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
#include "yaCharacterSelect.h"

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

		// Camera
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, true);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		// M2
		GameObject* m2textureObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		m2textureObj->SetName(L"M2Texture");
		Transform* m2textureTr = m2textureObj->GetComponent<Transform>();
		m2textureTr->SetPosition(Vector3(-5.8f, 0.0f, 1.0f));
		m2textureTr->SetScale(Vector3(4.5f, 9.5f, 1.0f));
		m2textureObj->AddComponent<CharacterSelect>();

		SpriteRenderer* m2Mr = m2textureObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> m2Material = Resources::Find<Material>(L"m2Material");
		m2Mr->SetMaterial(m2Material);
		m2Mr->SetMesh(mesh);

		// selectBG
		GameObject* selectObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		selectObj->SetName(L"Select");
		Transform* map1Tr = selectObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
		map1Tr->SetScale(Vector3(width / 50.0f, height / 50.0f, 1.0f));

		SpriteRenderer* selectMr = selectObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> selectMaterial = Resources::Find<Material>(L"SelectMaterial");
		selectMr->SetMaterial(selectMaterial);
		selectMr->SetMesh(mesh);

		//P1 Texture
		GameObject* p1textureObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		p1textureObj->SetName(L"P1Texture");
		Transform* p1textureTr = p1textureObj->GetComponent<Transform>();
		p1textureTr->SetPosition(Vector3(-6.0f, 4.7f, 1.0f));
		p1textureTr->SetScale(Vector3(1.5f, 1.5f, 1.0f));

		SpriteRenderer* p1Mr = p1textureObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> p1Material = Resources::Find<Material>(L"p1Material");
		p1Mr->SetMaterial(p1Material);
		p1Mr->SetMesh(mesh);

		

		Scene::Initalize();
	}
	void CharacterSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Stage1);
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