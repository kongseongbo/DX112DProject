#include "yaArabianScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaRigidbody.h"
#include "yaArabianKnifeScript.h"
#include "yaArabianKnife.h"


namespace ya
{
	ArabianScript::ArabianState ArabianScript::mArabianState = ArabianState::NEW;

	ArabianScript::ArabianScript()
		: Script()
		, mArabianAni(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, direction(-1)
		, index(0)
	{
		
	}
	ArabianScript::~ArabianScript()
	{
		mArabianState = ArabianState::NEW;
	}
	void ArabianScript::Initalize()
	{
	/*	if (index == 0)
			GetOwner()->SetName(L"Arabian1");
		if (index == 1)
			GetOwner()->SetName(L"Arabian2");
		if (index == 2)
			GetOwner()->SetName(L"Arabian3");*/


		Collider2D* arabianColl = GetOwner()->AddComponent<Collider2D>();
		arabianColl->SetType(eColliderType::Rect);
		arabianColl->SetCenter(Vector2(0.0f, 0.0f));
		arabianColl->SetSize(Vector2(0.2f, 0.2f));

		//GetOwner()->AddComponent<Rigidbody>();
		mTr = GetOwner()->GetComponent<Transform>();

		mArabianAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ArabianIdle", L"Arabian\\Idle.png");
		mArabianAni->Create(L"LeftIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 55.0f), Vector2::Zero, 6, 0.25f);
		
		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mArabianAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 52.0f), Vector2(0.05f, 0.0f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack", L"Arabian\\Attack.png");
		mArabianAni->Create(L"LeftAttack", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 65.0f), Vector2::Zero, 8, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianDeath", L"Arabian\\Death.png");
		mArabianAni->Create(L"LeftDeath", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 50.0f), Vector2::Zero, 11, 0.1f);
		
		texture = Resources::Load<Texture>(L"BombDeath", L"Arabian\\BombDeath.png");
		mArabianAni->Create(L"BombDeath", texture, Vector2(0.0f, 0.0f), Vector2(80.0f, 60.0f), Vector2::Zero, 13, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack2", L"Arabian\\Attack2.png");
		mArabianAni->Create(L"LeftKnifeAttack2", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 60.0f), Vector2(0.0f, -0.05), 19, 0.1f);

		texture = Resources::Load<Texture>(L"S", L"Arabian\\S.png");
		mArabianAni->Create(L"S", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 55.0f), Vector2(0.01f, 0.0f), 4, 0.3f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		mArabianAni->GetCompleteEvent(L"LeftAttack") = std::bind(&ArabianScript::Attack, this);
		mArabianAni->GetCompleteEvent(L"LeftKnifeAttack2") = std::bind(&ArabianScript::Attack, this);
		//mArabianAni->GetEvent(L"LeftKnifeAttack2", 4) = std::bind(&ArabianScript::AttackKnife, this);

		mArabianAni->Play(L"LeftMove", true);
	}
	void ArabianScript::Update()
	{
		
		if (GetOwner()->GetName() == L"Arabian1")
			int a = 0;
		switch (mArabianState)
		{
		case ya::ArabianScript::ArabianState::NEW:
			New();
			break;
		case ya::ArabianScript::ArabianState::IDLE:
			Idle();
			break;
		case ya::ArabianScript::ArabianState::MOVE:
			Move();
			break;
		case ya::ArabianScript::ArabianState::ATTACK:
			Attack();
			break;
		case ya::ArabianScript::ArabianState::DEATH:
			Death();
			break;
		default:
			break;
		}
	}
	void ArabianScript::FixedUpdate()
	{
	}
	void ArabianScript::Render()
	{
	}
	void ArabianScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head")
		{
			mArabianAni->Play(L"LeftAttack", false);
			//mArabianState = ArabianState::ATTACK;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			mArabianAni->Play(L"LeftDeath", false);
			mArabianState = ArabianState::DEATH;
			mTime = 0.0f;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			mArabianAni->Play(L"BombDeath", false);
			mArabianState = ArabianState::DEATH;
			mTime = 0.0f;
		}
	}
	void ArabianScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ArabianScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ArabianScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ArabianScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ArabianScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void ArabianScript::New()
	{
		Vector3 pos = mTr->GetPosition();
		pos.x -= 5.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		mTime += Time::DeltaTime();
		if (mTime > 0.5f)
		{
			mArabianAni->Play(L"LeftIdle", true);
			mArabianState = ArabianState::IDLE;
			mTime = 0.0f;
		}

	}
	void ArabianScript::Idle()
	{

		if (GetOwner()->GetName() == L"Arabian1")
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(0, 4);

			int a = 0;
			mTime += Time::DeltaTime();
			if (mTime > 2.0f)
			{
				a = distr(eng);
				mTime = 0.0f;
			}

			if (a == 1)
			{
				mArabianAni->Play(L"LeftKnifeAttack2", false);
				AttackKnife();
			}

			if (a == 2)
			{
				mTime = 0.0f;
				direction = 1;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
			if (a == 3)
			{
				mTime = 0.0f;
				direction = 0;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
		}

		if (GetOwner()->GetName() == L"Arabian2")
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(0, 4);

			int a = 0;
			mTime += Time::DeltaTime();
			if (mTime > 2.0f)
			{
				a = distr(eng);
				mTime = 0.0f;
			}

			if (a == 1)
			{
				mArabianAni->Play(L"LeftKnifeAttack2", false);
				AttackKnife();
			}

			if (a == 2)
			{
				mTime = 0.0f;
				direction = 1;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
			if (a == 3)
			{
				mTime = 0.0f;
				direction = 0;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
		}

		if (GetOwner()->GetName() == L"Arabian3")
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(0, 4);

			int a = 0;
			mTime += Time::DeltaTime();
			if (mTime > 2.0f)
			{
				a = distr(eng);
				mTime = 0.0f;
			}

			if (a == 1)
			{
				mArabianAni->Play(L"LeftKnifeAttack2", false);
				AttackKnife();
			}

			if (a == 2)
			{
				mTime = 0.0f;
				direction = 1;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
			if (a == 3)
			{
				mTime = 0.0f;
				direction = 0;
				mArabianAni->Play(L"S", true);
				mArabianState = ArabianState::MOVE;
			}
		}

	}
	void ArabianScript::Move()
	{
		if (GetOwner()->GetName() == L"Arabian1")
		{
			mTime += Time::DeltaTime();


			if (direction == 0)
			{
				Vector3 pos = mTr->GetPosition();
				pos.x -= 2.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

				if (mTime > 1.0f)
				{
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
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
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
					mTime = 0.0f;

				}

			}
		}

		if (GetOwner()->GetName() == L"Arabian2")
		{
			mTime += Time::DeltaTime();


			if (direction == 0)
			{
				Vector3 pos = mTr->GetPosition();
				pos.x -= 2.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

				if (mTime > 1.0f)
				{
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
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
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
					mTime = 0.0f;

				}

			}
		}

		if (GetOwner()->GetName() == L"Arabian3")
		{
			mTime += Time::DeltaTime();


			if (direction == 0)
			{
				Vector3 pos = mTr->GetPosition();
				pos.x -= 2.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

				if (mTime > 1.0f)
				{
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
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
					mArabianAni->Play(L"LeftIdle", true);
					mArabianState = ArabianState::IDLE;
					mTime = 0.0f;

				}

			}
		}
	}
	void ArabianScript::Attack()
	{
		mArabianAni->Play(L"LeftIdle", true);
		mArabianState = ArabianState::IDLE;
	}
	void ArabianScript::Death()
	{
		mTime += Time::DeltaTime();

		mTr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = mTr->GetPosition();
		pos.x += 5.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		if (mTime > 0.5f)
			GetOwner()->Death();
	}
	void ArabianScript::AttackKnife()
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