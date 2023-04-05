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

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(0.1f, 0.1f));

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		Animator* bulletAni = GetOwner()->AddComponent<Animator>();
		bulletAni->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		bulletAni->Play(L"BassBullet", true);
		
	}
	void BulletScript::Update()
	{
		Animator* bulletAni = GetOwner()->GetComponent<Animator>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		time += 1.5f * Time::DeltaTime();
		
		if (GetOwner()->GetName() == L"bullet0")
		{
			if (time > 2.0f)
			{
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
					//time = 0.0f;
					tr->SetPosition(pos);
				}
			}
		}
		if (GetOwner()->GetName() == L"bullet1")
		{
			if (time > 1.0f)
			{
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
					//time = 0.0f;
					tr->SetPosition(pos);
				}
			}
		}
		//else
		//{
		//	if (mStateUp)
		//	{
		//		pos.y += 30.f * Time::DeltaTime();
		//	}
		//	else
		//	{

		//		if (mDirection == 0)
		//			pos.x -= 30.f * Time::DeltaTime();
		//		else
		//			pos.x += 30.f * Time::DeltaTime();
		//		//time = 0.0f;
		//		tr->SetPosition(pos);
		//	}

		//	if (time > 5.0f)
		//	{
		//		GetOwner()->Death();
		//		time = 0.0f;
		//	}
		//}
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
