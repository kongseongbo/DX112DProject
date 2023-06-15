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
#include "yaLight.h"
#include "yaParticleSystem.h"

namespace ya
{
	BulletScript::BulletScript()
		: Script()
		, mDirection(0)
		, mTime(0.0f)
		, mStateUp(false)
		, mSpeed(0.0f)
		, mbCrash(false)
	{

	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Bullet);


		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(0.1f, 0.1f));

		Animator* bulletAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		bulletAni->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		texture = Resources::Load<Texture>(L"MachineGunBullet", L"Bullet\\MachineGunBullet.png");
		bulletAni->Create(L"MachineGunBullet", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 7.0f), Vector2::Zero, 1, 0.3f);

		texture = Resources::Load<Texture>(L"Effect", L"Bullet\\Effect.png");
		bulletAni->Create(L"Effect", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 16.0f), Vector2::Zero, 10, 0.1f);

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		
	}
	void BulletScript::Update()
	{
		Animator* bulletAni = GetOwner()->GetComponent<Animator>();
		
		mTime += 1.5f * Time::DeltaTime();

		if (mbCrash == false)
		{
			if (GetOwner()->GetName() == L"bullet")
			{
				bulletAni->Play(L"BassBullet", true);
				Attack(mTime, 0.0);
			}

			if (GetOwner()->GetName() == L"bullet0")
			{
				bulletAni->Play(L"MachineGunBullet", true);
				Attack(mTime, 0.0);
			}
			if (GetOwner()->GetName() == L"bullet1")
			{
				bulletAni->Play(L"MachineGunBullet", true);
				Attack(mTime, 0.1);
			}
			if (GetOwner()->GetName() == L"bullet2")
			{
				bulletAni->Play(L"MachineGunBullet", true);
				Attack(mTime, 0.15);
			}
			if (GetOwner()->GetName() == L"bullet3")
			{
				bulletAni->Play(L"MachineGunBullet", true);
				Attack(mTime, 0.2);
			}
			if (GetOwner()->GetName() == L"bullet4")
			{
				bulletAni->Play(L"MachineGunBullet", true);
				Attack(mTime, 0.25);
			}
		}
		else
		{
			if (mTime > 1.0f)
				GetOwner()->Death();
		}

		if (mTime > 1.5f)
			GetOwner()->Death();
	}
	void BulletScript::FixedUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Delete)
			return;

		//GetOwner()->SetLayerType(eLayerType::Effect);

		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"Effect", false);
		mbCrash = true;

		
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
	void BulletScript::Attack(float time, float attacktime)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (attacktime < time)
		{	
			if (mStateUp)
			{
				pos += tr->Right() * 30.f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else
			{
				if (mDirection == 0)
				{
					
					pos += tr->Right() * 30.f * Time::DeltaTime();
				}
				else
				{

					pos += tr->Right() * 30.f * Time::DeltaTime();
				}
			
				tr->SetPosition(pos);
			}
		}
	}
}
