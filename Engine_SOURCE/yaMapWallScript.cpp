#include "yaMapWallScript.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaSpriteRenderer.h"


#include "yaBradleyScript.h"
#include "yaBradley.h"
#include "yaTentScript.h"
namespace ya
{
	MapWallScript::MapWallScript()
		: Script()
		, mStack(0)
		, mPlayer(nullptr)
	{
	}
	MapWallScript::~MapWallScript()
	{
	}
	void MapWallScript::Initalize()
	{
		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Wall", L"Map\\Wall.png");
		ani->Create(L"Wall", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 151.0f), Vector2::Zero, 1, 0.3f);
		ani->Create(L"DestroyWall", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 151.0f), Vector2::Zero, 3, 0.2f);
		ani->Play(L"Wall", false);

		ani->GetCompleteEvent(L"DestroyWall") = std::bind(&MapWallScript::Destroy, this);
	}
	void MapWallScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mStack == 7)
			ani->Play(L"DestroyWall", false);

	}
	void MapWallScript::FixedUpdate()
	{
	}
	void MapWallScript::Render()
	{
	}
	void MapWallScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet && GetOwner()->GetName() == L"Wall")
		{
			mStack++;
			
		}

		if(collider->GetOwner()->GetLayerType() == eLayerType::Bomb && GetOwner()->GetName() == L"Wall")
		{
			mStack++;
		}
	}
	void MapWallScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MapWallScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MapWallScript::CreatMonster(Vector3 position)
	{
	}
	void MapWallScript::Destroy()
	{
		Scene* scene = SceneManager::GetActiveScene();
		{
			GameObject* obj = new GameObject();
			scene->AddGameObject(obj, eLayerType::Map);
			obj->SetName(L"Mission2Map");
			Transform* map1Tr = obj->GetComponent<Transform>();
			map1Tr->SetPosition(Vector3(127.6f, 1.0f, 9.0f));
			map1Tr->SetScale(Vector3(92.0f, 18.0f, 1.0f));

			SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"MapMaterial2");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(material);
			sr->SetMesh(mesh);
		}
#pragma region LeftTent
		{
			GameObject* obj = new GameObject();
			scene->AddGameObject(obj, eLayerType::Map);
			Transform* map1Tr = obj->GetComponent<Transform>();
			map1Tr->SetPosition(Vector3(151.75f, 2.0f, 8.0f));
			map1Tr->SetScale(Vector3(14.0f, 13.0f, 1.0f));

			Animator* ani = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"LeftTent", L"Map\\LeftTent.png");
			ani->Create(L"LeftTent", texture, Vector2(0.0f, 0.0f), Vector2(180.0f, 45.0f), Vector2::Zero, 4, 0.1f);

			SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(material);
			sr->SetMesh(mesh);

			ani->Play(L"LeftTent", true);
		}
#pragma endregion
#pragma region RightTent
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"Tent");
			scene->AddGameObject(obj, eLayerType::Map);
			Transform* map1Tr = obj->GetComponent<Transform>();
			map1Tr->SetPosition(Vector3(170.5f, 2.0f, 8.0f));
			map1Tr->SetScale(Vector3(14.0f, 13.0f, 1.0f));

			obj->AddComponent<Animator>();
			Collider2D* coll =obj->AddComponent<Collider2D>();
			coll->SetType(eColliderType::Rect);
			coll->SetSize(Vector2(0.1, 0.15));
			obj->AddComponent<TentScript>();

			SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(material);
			sr->SetMesh(mesh);
		}
#pragma endregion
#pragma region BRADLEY
		{
			Bradley* bradley = new Bradley();
			scene->AddGameObject(bradley, eLayerType::Monster);
			bradley->SetName(L"Bradley");
			Transform* tr = bradley->GetComponent<Transform>();
			tr->SetPosition(Vector3(87.0f, -2.4f, 5.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			bradley->AddComponent<Animator>();
			BradleyScript* bradleyScript = bradley->AddComponent<BradleyScript>();
			bradleyScript->SetPlayer(mPlayer);

			SpriteRenderer* sr = bradley->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(matateiral);
			sr->SetMesh(mesh);
		}
#pragma endregion


		GetOwner()->SetState(GameObject::Dead);
	}
}