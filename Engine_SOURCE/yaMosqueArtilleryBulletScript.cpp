#include "yaMosqueArtilleryBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaLight.h"

#include "yaMosqueArtilleryBulletEffectScript.h"


namespace ya
{
	MosqueArtilleryBulletScript::MosqueArtilleryBulletScript()
		: Script()
		, mTargetPos{}
		, mDirection(0)
		, mSpeed(0.0f)
		, mTime(0.0f)
		, mStateUp(false)
	{

	}
	MosqueArtilleryBulletScript::~MosqueArtilleryBulletScript()
	{
	}
	void MosqueArtilleryBulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterAttack);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetCenter(Vector2(0.0f, 0.0f));
		coll->SetSize(Vector2(0.1f, 0.1f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bullet", L"MosqueArtillery\\Bullet.png");
		ani->Create(L"MosqueBullet", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 60.0f), Vector2::Zero, 3, 0.1f);

		texture = Resources::Load<Texture>(L"BulletBomb", L"MosqueArtillery\\BulletBomb.png");
		ani->Create(L"BulletBomb", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 38.0f), Vector2::Zero, 15, 0.1f);
	
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		sr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		ani->Play(L"MosqueBullet", true);

		ani->GetCompleteEvent(L"BulletBomb") = std::bind(&MosqueArtilleryBulletScript::DeadBullet, this);

	}
	void MosqueArtilleryBulletScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		Attack(mTargetPos);
	}
	void MosqueArtilleryBulletScript::FixedUpdate()
	{
	}
	void MosqueArtilleryBulletScript::Render()
	{
	}
	void MosqueArtilleryBulletScript::OnCollisionEnter(Collider2D* collider)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		GameObject* effectObj = object::Instantiate<GameObject>(eLayerType::Effect);
		Transform* effectTr = effectObj->GetComponent<Transform>();
		effectTr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y, 1.0f));
		effectTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

		effectObj->AddComponent<MosqueArtilleryBulletEffectScript>();

		GetOwner()->Death();
	}
	void MosqueArtilleryBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void MosqueArtilleryBulletScript::DeadBullet()
	{
	}
	void MosqueArtilleryBulletScript::Attack(Vector3 pos)
	{
		mTime += 2.0f * Time::DeltaTime();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 trPos = tr->GetPosition();
		
		//trPos -= tr->Up() * 10.f * Time::DeltaTime();
		
		//tr->SetPosition(trPos);

		float amplitude = 30.0f; // amplitude of the sine wave
		float frequency = 1.0f; // frequency of the sine wave

		float dx = mTargetPos.x - trPos.x;
		float dy = mTargetPos.y - trPos.y;
		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance > 0.1f)
		{
			dx /= distance;
			dy /= distance;

			

			if (mTime > 1.0f)
			{
				std::random_device rd;
				std::mt19937 eng(rd());
				std::uniform_real_distribution<> distr(0, 3);

				if (distr(eng) >= 2)
				{
					tr->SetRotation(Vector3(0.0f, 0.0f, 90.0f));
					mTime = 0.0f;
				}

				if (distr(eng) < 2 && distr(eng) > 1)
				{
					tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
					mTime = 0.0f;
				}

				if (distr(eng) <= 1)
				{
					tr->SetRotation(Vector3(0.0f, 0.0f, 280.0f));
					mTime = 0.0f;
				}
			}
			trPos += tr->Right() * dx * 3.0f * Time::DeltaTime();
			trPos += tr->Up() * dy * 3.0f * Time::DeltaTime();

			// update object position
			tr->SetPosition(trPos);
		}
	}
}