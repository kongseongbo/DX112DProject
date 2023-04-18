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
	ArabianScript::ArabianState ArabianScript::mArabianState = ArabianState::IDLE;

	ArabianScript::ArabianScript()
		: Script()
		, mArabianAni(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
	{
	}
	ArabianScript::~ArabianScript()
	{
	}
	void ArabianScript::Initalize()
	{
		Collider2D* arabianColl = GetOwner()->AddComponent<Collider2D>();
		arabianColl->SetType(eColliderType::Rect);
		arabianColl->SetCenter(Vector2(0.0f, 0.0f));
		arabianColl->SetSize(Vector2(0.2f, 0.2f));

		//GetOwner()->AddComponent<Rigidbody>();
		mTr = GetOwner()->GetComponent<Transform>();

		mArabianAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ArabianIdle", L"Arabian\\Idle.png");
		mArabianAni->Create(L"LeftIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 55.0f), Vector2::Zero, 6, 0.2f);
		
		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mArabianAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 52.0f), Vector2::Zero, 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack", L"Arabian\\Attack.png");
		mArabianAni->Create(L"LeftAttack", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 65.0f), Vector2(-0.02f,-0.05f), 8, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianDeath", L"Arabian\\Death.png");
		mArabianAni->Create(L"LeftDeath", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 50.0f), Vector2::Zero, 11, 0.1f);
		
		texture = Resources::Load<Texture>(L"ArabianAttack2", L"Arabian\\Attack2.png");
		mArabianAni->Create(L"LeftAttack2", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 60.0f), Vector2(0.0f, -0.05), 19, 0.15f);



		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		mArabianAni->Play(L"LeftIdle", true);

		mArabianAni->GetCompleteEvent(L"LeftAttack") = std::bind(&ArabianScript::Attack, this);
		mArabianAni->GetCompleteEvent(L"LeftAttack2") = std::bind(&ArabianScript::Attack, this);
		mArabianAni->GetEvent(L"LeftAttack2", 3) = std::bind(&ArabianScript::AttackKnife, this);
	}
	void ArabianScript::Update()
	{
		switch (mArabianState)
		{
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
		if (collider->GetID() == 1)
		{
			mArabianAni->Play(L"LeftAttack", false);
			//mArabianState = ArabianState::ATTACK;
		}

		if (collider->GetID() == 7)
		{
			mArabianAni->Play(L"LeftDeath", false);
			mTime = 0.0f;
			mArabianState = ArabianState::DEATH;
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
	void ArabianScript::Idle()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			mArabianAni->Play(L"LeftAttack2", false);
			mTime = 0.0f;
		}

	}
	void ArabianScript::Move()
	{
	}
	void ArabianScript::Attack()
	{
		//mTime = 0.0f;

		mArabianAni->Play(L"LeftIdle", true);
		mArabianState = ArabianState::IDLE;

		
	}
	void ArabianScript::Death()
	{
		mTime += Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();	
		pos.x += 5.0f * Time::DeltaTime();

		if (mTime > 0.5f)
			GetOwner()->Death();

		tr->SetPosition(pos);
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