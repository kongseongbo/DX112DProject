#include "yaMosqueArtilleryBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaLight.h"


namespace ya
{
	MosqueArtilleryBulletScript::MosqueArtilleryBulletScript()
		: Script()
	{
	}
	MosqueArtilleryBulletScript::~MosqueArtilleryBulletScript()
	{
	}
	void MosqueArtilleryBulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterAttack);


		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));


		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetCenter(Vector2(0.0f, 0.0f));
		coll->SetSize(Vector2(0.1f, 0.1f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		ani->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);
	
		ani->Play(L"BassBullet", true);
	}
	void MosqueArtilleryBulletScript::Update()
	{
		
	}
	void MosqueArtilleryBulletScript::FixedUpdate()
	{
	}
	void MosqueArtilleryBulletScript::Render()
	{
	}
	void MosqueArtilleryBulletScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletScript::Attack(Vector3 pos)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();

		pos -= tr->Up() * 10.f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
}