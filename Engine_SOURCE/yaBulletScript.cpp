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

namespace ya
{
	BulletScript::BulletScript()
		: Script()
		, mDirection(0)
		, mTime(0.0f)
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


		/*Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));*/
		

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(0.1f, 0.1f));

		Animator* bulletAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		bulletAni->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		texture = Resources::Load<Texture>(L"MachineGunBullet", L"Bullet\\MachineGunBullet.png");
		bulletAni->Create(L"MachineGunBullet", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 7.0f), Vector2::Zero, 1, 0.3f);

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
			Attack(mTime, 0.05);
		}
		if (GetOwner()->GetName() == L"bullet2")
		{
			bulletAni->Play(L"MachineGunBullet", true);
			Attack(mTime, 0.1);
		}
		if (GetOwner()->GetName() == L"bullet3")
		{
			bulletAni->Play(L"MachineGunBullet", true);
			Attack(mTime, 0.15);
		}
		if (GetOwner()->GetName() == L"bullet4")
		{
			bulletAni->Play(L"MachineGunBullet", true);
			Attack(mTime, 0.2);
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
	void BulletScript::Attack(float time, float attacktime)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (attacktime < time)
		{
			Vector3 v = Vector3::Lerp(Vector3(2, 0, 0), Vector3(0, 2, 0), 2.0f);
			
			if (mStateUp)
			{
				pos.y += 30.f * Time::DeltaTime();
				//pos.x += 15.f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else
			{
				if (mDirection == 0)
					pos.x -= 30.f * Time::DeltaTime();
				else
					pos.x += 30.f * Time::DeltaTime();
			
				tr->SetPosition(pos);
			}
		}
	}
}
// 러프함수