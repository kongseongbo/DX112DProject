#include "yaBombScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaHeadScript.h"
#include "yaInput.h"
#include "yaRigidbody.h"

namespace ya
{
	BombScript::BombScript()
		: Script()
		, stack(0)
	{
	}
	BombScript::~BombScript()
	{
	}
	void BombScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Bomb);

		Collider2D* bombColl = GetOwner()->AddComponent<Collider2D>();
		bombColl->SetType(eColliderType::Rect);
		bombColl->SetCenter(Vector2(0.0f, 0.0f));
		bombColl->SetSize(Vector2(0.1f, 0.1f));
		
		GetOwner()->AddComponent<Rigidbody>();

		Animator* bombAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bomb", L"Bullet\\Bomb.png");
		bombAni->Create(L"Bomb", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 16, 0.1f);

		texture = Resources::Load<Texture>(L"BombEffect", L"Bullet\\BombEffect.png");
		bombAni->Create(L"BombEffect", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 63.0f), Vector2(0.05f,0.0f), 6, 0.1f);

		SpriteRenderer* bombSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bombMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bombSr->SetMaterial(bombMaterial);
		bombSr->SetMesh(mesh);

		bombAni->Play(L"Bomb", true);

		bombAni->GetCompleteEvent(L"BombEffect") = std::bind(&BombScript::End, this);
	}
	void BombScript::Update()
	{
		if (stack < 2)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void BombScript::FixedUpdate()
	{
	}
	void BombScript::Render()
	{
	}
	void BombScript::OnCollisionEnter(Collider2D* collider)
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();

		if (stack >= 2)
		{
			Animator* bombAni = GetOwner()->GetComponent<Animator>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 rot = tr->GetRotation();
			rot.z = 90.0f;
			tr->SetRotation(rot);
			bombAni->Play(L"BombEffect", false);
			rigidbody->SetGround(true);
		}
		else
		{
			velocity.y = 20.0f;
			rigidbody->SetGround(false);
			rigidbody->SetVelocity(velocity);
			++stack;
		}
	}
	void BombScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BombScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void BombScript::End()
	{
		GetOwner()->Death();
	}
}