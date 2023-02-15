#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"

namespace ya
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initalize();

		// Camera GmaeObject
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);

		mPlayScene->AddGameObject(cameraObj, eLayerType::Camera);

		// SMILE RECT
		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr <Material> mateiral = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		mPlayScene->AddGameObject(obj, eLayerType::Player);

		// DefaultSprite
		GameObject* spriteObj = new GameObject();
		Transform* spriteTr = new Transform();
		spriteTr->SetPosition(Vector3(5.0f, 0.0f, 10.0f));
		spriteObj->AddComponent(spriteTr);

		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mPlayScene->AddGameObject(spriteObj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
	void SceneManager::Release()
	{
		delete mPlayScene;
		mPlayScene = nullptr;
	}
}