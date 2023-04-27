#include "yaArabian2Script.h"
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
	Arabian2Script::Arabian2Script()
		: Script()
		, mArabianAni(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, direction(-1)
	{

	}
	Arabian2Script::~Arabian2Script()
	{
		mArabian2State = Arabian2State::NEW;
	}
	void Arabian2Script::Initalize()
	{
		mArabian2State = Arabian2State::NEW;
		Collider2D* arabianColl = GetOwner()->AddComponent<Collider2D>();
		arabianColl->SetType(eColliderType::Rect);
		arabianColl->SetCenter(Vector2(0.0f, 0.0f));
		arabianColl->SetSize(Vector2(0.2f, 0.2f));

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

		mArabianAni->GetCompleteEvent(L"LeftAttack") = std::bind(&Arabian2Script::Attack, this);
		mArabianAni->GetCompleteEvent(L"LeftKnifeAttack2") = std::bind(&Arabian2Script::Attack, this);
		//mArabianAni->GetEvent(L"LeftKnifeAttack2", 4) = std::bind(&ArabianScript::AttackKnife, this);

		mArabianAni->Play(L"LeftMove", true);
	}
	void Arabian2Script::Update()
	{


		switch (mArabian2State)
		{
		case ya::Arabian2Script::Arabian2State::NEW:
			New();
			break;
		case ya::Arabian2Script::Arabian2State::IDLE:
			Idle();
			break;
		case ya::Arabian2Script::Arabian2State::MOVE:
			Move();
			break;
		case ya::Arabian2Script::Arabian2State::ATTACK:
			Attack();
			break;
		case ya::Arabian2Script::Arabian2State::DEATH:
			Death();
			break;
		default:
			break;
		}
	}
	void Arabian2Script::FixedUpdate()
	{
	}
	void Arabian2Script::Render()
	{
	}
	void Arabian2Script::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head")
		{
			mArabianAni->Play(L"LeftAttack", false);
			//mArabianState = ArabianState::ATTACK;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			mArabianAni->Play(L"LeftDeath", false);
			mArabian2State = Arabian2State::DEATH;
			mTime = 0.0f;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			mArabianAni->Play(L"BombDeath", false);
			mArabian2State = Arabian2State::DEATH;
			mTime = 0.0f;
		}
	}
	void Arabian2Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void Arabian2Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void Arabian2Script::OnTriggerEnter(Collider2D* collider)
	{
	}
	void Arabian2Script::OnTriggerStay(Collider2D* collider)
	{
	}
	void Arabian2Script::OnTriggerExit(Collider2D* collider)
	{
	}
	void Arabian2Script::New()
	{
		Vector3 pos = mTr->GetPosition();
		pos.x -= 5.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		mTime += Time::DeltaTime();
		if (mTime > 0.5f)
		{
			mArabianAni->Play(L"LeftIdle", true);
			mArabian2State = Arabian2State::IDLE;
			mTime = 0.0f;
		}

	}
	void Arabian2Script::Idle()
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
			mArabian2State = Arabian2State::MOVE;
		}
		if (a == 3)
		{
			mTime = 0.0f;
			direction = 0;
			mArabianAni->Play(L"S", true);
			mArabian2State = Arabian2State::MOVE;
		}
	}
	void Arabian2Script::Move()
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
				mArabian2State = Arabian2State::IDLE;
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
				mArabian2State = Arabian2State::IDLE;
				mTime = 0.0f;

			}
		}
	}
	void Arabian2Script::Attack()
	{
		mArabianAni->Play(L"LeftIdle", true);
		mArabian2State = Arabian2State::IDLE;
	}
	void Arabian2Script::Death()
	{
		mTime += Time::DeltaTime();

		mTr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = mTr->GetPosition();
		pos.x += 5.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		if (mTime > 0.5f)
			GetOwner()->Death();
	}
	void Arabian2Script::AttackKnife()
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