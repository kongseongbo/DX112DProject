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
#include "yaCollider2D.h"
#include "yaApplication.h"

extern ya::Application application;

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
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);


		float width = (winRect.right - winRect.left);
		float height = (winRect.bottom - winRect.top);

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// Title
		GameObject* titleObj = object::Instantiate<GameObject>(eLayerType::Map, this);
		titleObj->SetName(L"Title");
		Transform* map1Tr = titleObj->GetComponent<Transform>();
		map1Tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
		map1Tr->SetScale(Vector3(width / 100.0f, height / 100.0f, 1.0f));

		SpriteRenderer* titleMr = titleObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> titleMaterial = Resources::Find<Material>(L"TitleMaterial");
		titleMr->SetMaterial(titleMaterial);
		titleMr->SetMesh(mesh);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::CharacterSelect);
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