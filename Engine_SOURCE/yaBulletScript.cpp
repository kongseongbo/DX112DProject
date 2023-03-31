#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"



namespace ya
{
	BulletScript::BulletScript()
		: Script()
	{
	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initalize()
	{
		/*Collider2D* bodyCollider = AddComponent<Collider2D>();
		bodyCollider->SetType(eColliderType::Rect);
		bodyCollider->SetCenter(Vector2(-0.5f, -1.0f));
		bodyCollider->SetSize(Vector2(0.1f, 0.05f));*/

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		Animator* bulletAni = GetOwner()->AddComponent<Animator>();
		bulletAni->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		SpriteRenderer* bodyMr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bodyMr->SetMaterial(bodyMateiral);
		bodyMr->SetMesh(mesh);

		bulletAni->Play(L"BassBullet", true);

	}
	void BulletScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 10.0f* Time::DeltaTime();

		tr->SetPosition(pos);

	
	}
	void BulletScript::FixedUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BulletScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BulletScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BulletScript::OnTriggerExit(Collider2D* collider)
	{
	}

}
