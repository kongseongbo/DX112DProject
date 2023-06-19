#include "yaBossArabianScript.h"
#include "yaSceneManager.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaCollider2D.h"
#include "yaRigidbody.h"

#include "yaArabianKnifeScript.h"
#include "yaArabianKnife.h"

namespace ya
{
	BossArabianScript::BossArabianScript()
		: Script()
		, mBossArabianState(BossArabianState::NEW)
		, mAni(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, index(0)
		, direction(0)
		, ox(false)
	{
	}
	BossArabianScript::~BossArabianScript()
	{
	}
	void BossArabianScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.1f, 0.2f));

		mAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ArabianIdle", L"Arabian\\Idle.png");
		mAni->Create(L"ArabianIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 55.0f), Vector2::Zero, 6, 0.25f);

		texture = Resources::Load<Texture>(L"ArabianJump", L"Arabian\\Jump.png");
		mAni->Create(L"LeftArabianJump", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 50.0f), Vector2(0.0f, 0.0f), 9, 0.05f);
		mAni->Create(L"RightArabianJump", texture, Vector2(0.0f, 50.0f), Vector2(50.0f, 50.0f), Vector2(0.0f, 0.0f), 9, 0.05f);

		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 52.0f), Vector2(0.0f, 0.0f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mAni->Create(L"RightMove", texture, Vector2(0.0f, 52.0f), Vector2(54.0f, 52.0f), Vector2(0.0f, 0.0f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack", L"Arabian\\Attack.png");
		mAni->Create(L"Attack", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 65.0f), Vector2::Zero, 8, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianDeath", L"Arabian\\Death.png");
		mAni->Create(L"Death", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 50.0f), Vector2::Zero, 11, 0.1f);

		texture = Resources::Load<Texture>(L"BombDeath", L"Arabian\\BombDeath.png");
		mAni->Create(L"BombDeath", texture, Vector2(0.0f, 0.0f), Vector2(80.0f, 60.0f), Vector2::Zero, 13, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack2", L"Arabian\\Attack2.png");
		mAni->Create(L"KnifeAttack", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 60.0f), Vector2(0.0f, -0.05), 19, 0.1f);

		texture = Resources::Load<Texture>(L"Moving", L"Arabian\\Moving.png");
		mAni->Create(L"Moving", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 55.0f), Vector2(0.01f, 0.0f), 4, 0.3f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		mAni->Play(L"RightMove", true);
	}
	void BossArabianScript::Update()
	{
		switch (mBossArabianState)
		{
		case ya::BossArabianScript::BossArabianState::NEW:
			New();
			break;
		case ya::BossArabianScript::BossArabianState::JUMP:
			Jump();
			break;
		case ya::BossArabianScript::BossArabianState::IDLE:
			Idle();
			break;
		case ya::BossArabianScript::BossArabianState::MOVE:
			Move();
			break;
		case ya::BossArabianScript::BossArabianState::ATTACK:
			Attack();
			break;
		case ya::BossArabianScript::BossArabianState::DEATH:
			Death();
			break;
		default:
			break;
		}
	}
	void BossArabianScript::FixedUpdate()
	{
	}
	void BossArabianScript::Render()
	{
	}
	void BossArabianScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Tent")
		{
			mTime = 0.0f;
			ox = true;
			mAni->Play(L"LeftArabianJump", false);
			mBossArabianState = BossArabianState::JUMP;
		}

		if (collider->GetOwner()->GetName() == L"RectCollMap")
		{
			mTime = 0.0f;
			mAni->Play(L"ArabianIdle", false);
			mBossArabianState = BossArabianState::IDLE;
		}

		if (collider->GetOwner()->GetName() == L"Head")
		{
			mAni->Play(L"Attack", false);
			//mArabianState = ArabianState::ATTACK;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			mAni->Play(L"Death", false);
			mBossArabianState = BossArabianState::DEATH;
			mTime = 0.0f;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			mAni->Play(L"BombDeath", false);
			mBossArabianState = BossArabianState::DEATH;
			mTime = 0.0f;
		}
	}
	void BossArabianScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BossArabianScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BossArabianScript::New()
	{
		mTime += 2.0f * Time::DeltaTime();

		Vector3 pos = mTr->GetPosition();

		if (mTime > 2.0f)
		{
			mAni->Play(L"RightArabianJump", false);
			mBossArabianState = BossArabianState::JUMP;
		}
		else
		{
			pos.x += 3.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
	}
	void BossArabianScript::Jump()
	{
		mTime += 2.0f * Time::DeltaTime();
		Vector3 pos = mTr->GetPosition();

		if (ox == true)
		{
			if (mTime > 0.5f)
			{
				pos.x -= 3.0f * Time::DeltaTime();
				pos.y -= 6.0f * Time::DeltaTime();
				mTr->SetPosition(pos);
			}
			else
			{
				pos.x -= 3.5f * Time::DeltaTime();
				pos.y += 3.0f * Time::DeltaTime();
				mTr->SetPosition(pos);
			}
		}
		if (ox == false)
		{
			if (mTime > 2.5f)
			{

				pos.x += 5.0f * Time::DeltaTime();
				pos.y -= 4.0f * Time::DeltaTime();
				mTr->SetPosition(pos);
			}
			else
			{

				pos.x += 5.5f * Time::DeltaTime();
				pos.y += 5.0f * Time::DeltaTime();
				mTr->SetPosition(pos);
			}
		}
	}
	void BossArabianScript::Idle()
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> distr(0, 4);

		int a = 0;
		mTime += Time::DeltaTime();
		if (mTime > 1.5f)
		{
			a = distr(eng);
			mTime = 0.0f;
		}

		if (a == 1)
		{
			mAni->Play(L"KnifeAttack", false);
			AttackKnife();
		}

		if (a == 2)
		{
			mTime = 0.0f;
			direction = 1;
			mAni->Play(L"Moving", true);
			mBossArabianState = BossArabianState::MOVE;
		}
		if (a == 3)
		{
			mTime = 0.0f;
			direction = 0;
			mAni->Play(L"Moving", true);
			mBossArabianState = BossArabianState::MOVE;
		}
	}

	
	void BossArabianScript::Move()
	{
		mTime += Time::DeltaTime();


		if (direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 2.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			if (mTime > 1.0f)
			{
				mAni->Play(L"ArabianIdle", true);
				mBossArabianState = BossArabianState::IDLE;
				mTime = 0.0f;
			}
		}

		if (direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 2.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			if (mTime > 1.0f)
			{
				mAni->Play(L"ArabianIdle", true);
				mBossArabianState = BossArabianState::IDLE;
				mTime = 0.0f;

			}
		}
	}

	void BossArabianScript::Attack()
	{
		mAni->Play(L"ArabianIdle", true);
		mBossArabianState = BossArabianState::IDLE;
	}

	void BossArabianScript::Death()
	{
		mTime += Time::DeltaTime();

		mTr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = mTr->GetPosition();
		pos.x += 5.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		if (mTime > 0.5f)
			GetOwner()->Death();
	}

	void BossArabianScript::AttackKnife()
	{
		ArabianKnife* knife = new ArabianKnife();
		knife->SetName(L"knife");
		ArabianKnifeScript* knifeScript = knife->AddComponent<ArabianKnifeScript>();
		Transform* knifeTr = knife->GetComponent<Transform>();
		knifeTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y, mTr->GetPosition().z - 1));
		knifeTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		Rigidbody* knifeRigidbody = knife->GetComponent<Rigidbody>();
		Vector2 velocity = knifeRigidbody->GetVelocity();
		velocity.y = 50.0f;
		knifeRigidbody->SetGround(false);
		knifeRigidbody->SetVelocity(velocity);
	}
}