#include "yaHelicopterBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaLight.h"



namespace ya
{
	HelicopterBulletScript::HelicopterBulletScript()
		: Script()
		, mTr(nullptr)
		, mPlayerTr{}
		, pos{}
		, mTime(0.0f)
		, mRot(0.0f)
	{

	}
	HelicopterBulletScript::~HelicopterBulletScript()
	{
	}
	void HelicopterBulletScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		GetOwner()->SetLayerType(eLayerType::MonsterAttack);
		Light* light = GetOwner()->AddComponent<Light>();
		light->SetType(eLightType::Point);
		light->SetRadius(2.5f);
		light->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetCenter(Vector2(0.0f, 0.0f));
		coll->SetSize(Vector2(0.1f, 0.1f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		ani->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		SpriteRenderer* heliSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		heliSr->SetMaterial(heliMaterial);
		heliSr->SetMesh(mesh);

		ani->Play(L"BassBullet", false);
	}
	void HelicopterBulletScript::Update()
	{
		pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mTr->SetRotation(Vector3(1.0f, 1.0f, mRot));
		pos -= mTr->Right() * 10.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

	}
	void HelicopterBulletScript::FixedUpdate()
	{
	}
	void HelicopterBulletScript::Render()
	{
	}
	void HelicopterBulletScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void HelicopterBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void HelicopterBulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
}