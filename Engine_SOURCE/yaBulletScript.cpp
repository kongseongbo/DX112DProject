#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaHeadScript.h"
#include "yaInput.h"


namespace ya
{
	BulletScript::BulletScript()
		: Script()
		, mDirection(0)
		, time(0.0f)
		, mStateUp(false)
		, mSpeed(0.0f)
	{

	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Bullet);

		Collider2D* bodyCollider = GetOwner()->AddComponent<Collider2D>();
		bodyCollider->SetType(eColliderType::Rect);
		bodyCollider->SetCenter(Vector2(0.0f, 0.0f));
		bodyCollider->SetSize(Vector2(0.1f, 0.1f));

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
		Animator* bulletAni = GetOwner()->GetComponent<Animator>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		



		if (mStateUp)
		{
			pos.y += 30.f * Time::DeltaTime();
		}
		else
		{
			if (mDirection == 0)
				pos.x -= 30.f * Time::DeltaTime();
			else
				pos.x += 30.f * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		
	
	


		time += 1.5f * Time::DeltaTime();
		if (time > 2.0f)
		{
			GetOwner()->Death();

			time = 0.0f;
		}
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
