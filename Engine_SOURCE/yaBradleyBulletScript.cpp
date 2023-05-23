#include "yaBradleyBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"


namespace ya
{
	BradleyBulletScript::BradleyBulletScript()
		: Script()
		, mTime(0.0f)
		, mRot(0.0f)
		, mInitRot(0.0f)
	{
	}
	BradleyBulletScript::~BradleyBulletScript()
	{
	}
	void BradleyBulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterAttack);

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BradleyMissile", L"Bradley\\Missile2.png");
		ani->Create(L"BradleyMissile", texture, Vector2(0.0f, 0.0f), Vector2(55.0f, 16.0f), Vector2::Zero, 1, 0.2f);

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.2f, 0.08f));

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->Play(L"BradleyMissile", false);
	}
	void BradleyBulletScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if(mInitRot == -70.0f)
			HowitzerAttack(tr->GetPosition(), mTime, 0.2);
		if (mInitRot == 0.0f)
			NormalAttack(tr->GetPosition(), mTime, 0.2);
	}
	void BradleyBulletScript::FixedUpdate()
	{
	}
	void BradleyBulletScript::Render()
	{
	}
	void BradleyBulletScript::OnCollisionEnter(Collider2D* collider)
	{
		GetOwner()->Death();
	}
	void BradleyBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BradleyBulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BradleyBulletScript::HowitzerAttack(Vector3 position, float time, float attackTime)
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 rot = tr->GetRotation();


	
		mRot = rot.z += 85.f * Time::DeltaTime();
		pos -= tr->Right() * 8.f * Time::DeltaTime();

		if (mRot < 70.0f)
			tr->SetRotation(Vector3(rot.x, rot.y, mRot));

		tr->SetPosition(pos);
		
	}
	void BradleyBulletScript::NormalAttack(Vector3 position, float time, float attackTime)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 rot = tr->GetRotation();

		mRot = rot.z += 5.f * Time::DeltaTime();
		pos -= tr->Right() * 8.f * Time::DeltaTime();
		tr->SetRotation(Vector3(rot.x, rot.y, mRot));
		tr->SetPosition(pos);
	}
}