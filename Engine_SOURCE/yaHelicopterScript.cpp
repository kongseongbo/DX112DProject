#include "yaHelicopterScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaRigidbody.h"


#include "yaHelicopterBulletScript.h"

namespace ya
{
	HelicopterScript::HelicopterScript()
		: Script()
		, mHeliState(HeliState::MOVE)
		, mTr(nullptr)
		, mPlayer(nullptr)
		, mRot(0.0f)
		, mTime(0.0f)
		, mMoveTime(0.0f)
		, mStack(0)
		, ox(false)
	{
	}
	HelicopterScript::~HelicopterScript()
	{
	}
	void HelicopterScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* heliColl = GetOwner()->AddComponent<Collider2D>();
		heliColl->SetType(eColliderType::Rect);
		heliColl->SetSize(Vector2(0.1f, 0.1f));

		Animator* heliAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"LeftIdle", L"Helicopter\\LeftIdle.png");
		heliAni->Create(L"Left0", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftIdle2", L"Helicopter\\LeftIdle2.png");
		heliAni->Create(L"Left02", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftMove", L"Helicopter\\LeftMove.png");
		heliAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);
		heliAni->Create(L"LeftMove2", texture, Vector2(0.0f, 80.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"Rotation", L"Helicopter\\Rotation.png");
		heliAni->Create(L"Left18", texture, Vector2(0.0f, 0.0f), Vector2(80.0f, 90.0f), Vector2(0.01f,0.0f), 6, 0.1f);
		heliAni->Create(L"Left36", texture, Vector2(0.0f, 90.0f), Vector2(80.0f, 90.0f), Vector2(0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Left54", texture, Vector2(0.0f, 180.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);

		heliAni->Create(L"90", texture, Vector2(0.0f, 270.0f), Vector2(80.0f, 90.0f), Vector2::Zero, 6, 0.1f);

		heliAni->Create(L"Right54", texture, Vector2(0.0f, 360.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Right36", texture, Vector2(0.0f, 450.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Right18", texture, Vector2(0.0f, 540.0f), Vector2(80.0f, 90.0f), Vector2(0.01f, 0.0f), 6, 0.1f);

		texture = Resources::Load<Texture>(L"DeathEffect", L"Helicopter\\DeathEffect.png");
		heliAni->Create(L"heliDeath", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 56.0f), Vector2(0.01f, 0.0f), 6, 0.2f);

		SpriteRenderer* heliSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		heliSr->SetMaterial(heliMaterial);
		heliSr->SetMesh(mesh);

		heliAni->Play(L"Left0", true);

		heliAni->GetCompleteEvent(L"heliDeath") = std::bind(&HelicopterScript::End, this);
	}
	void HelicopterScript::Update()
	{
		mTime += 1.0f * Time::DeltaTime();
		mMoveTime += 1.0f * Time::DeltaTime();

		switch (mHeliState)
		{
		case ya::HelicopterScript::HeliState::MOVE:
			Move();
			break;
		case ya::HelicopterScript::HeliState::DIE:
			Die();
			break;
		default:
			break;
		}
	}
	void HelicopterScript::FixedUpdate()
	{
	}
	void HelicopterScript::Render()
	{
	}
	void HelicopterScript::OnCollisionEnter(Collider2D* collider)
	{
		Animator* heliAni = GetOwner()->GetComponent<Animator>();

		mStack++;
		if (mStack == 23)
		{
			heliAni->Play(L"heliDeath", false);
			mHeliState = HeliState::DIE;
		}
	}
	void HelicopterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void HelicopterScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void HelicopterScript::End()
	{
		GetOwner()->Death();
	}
	void HelicopterScript::Move()
	{
		Animator* heliAni = GetOwner()->GetComponent<Animator>();

		Vector3 playerPos = mPlayer->GetComponent<Transform>()->GetPosition();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 rot = GetOwner()->GetComponent<Transform>()->GetRotation();

		float aaa = atan2(playerPos.y - pos.y, playerPos.x - pos.x);
		mRot = fmodf((aaa * (180.0f / XM_PI) + 180.0f), 360.0f);

		if (mRot <= 65.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Left18"))
				heliAni->Play(L"Left18", true);
		}

		if (mRot >= 65.0f && mRot <= 75.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Left36"))
				heliAni->Play(L"Left36", true);
		}

		if (mRot >= 75.0f && mRot <= 85.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Left54"))
				heliAni->Play(L"Left54", true);
		}

		if (mRot >= 85.0f && mRot <= 95.0f)
		{
			if (!heliAni->IsAnimationRunning(L"90"))
				heliAni->Play(L"90", true);
		}

		if (mRot >= 95.0f && mRot <= 105.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Right18"))
				heliAni->Play(L"Right18", true);
		}

		if (mRot >= 105.0f && mRot <= 115.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Right36"))
				heliAni->Play(L"Right36", true);
		}

		if (mRot >= 115.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Right54"))
				heliAni->Play(L"Right54", true);
		}

		if (ox == true)
		{
			if (mMoveTime < 3.0f)
			{

				pos.x -= 3.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

			}
			if (mMoveTime < 6.0f && mMoveTime > 3.0f)
			{

				pos.x += 3.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

			}

			if (mMoveTime >= 6.0f)
			{
				mMoveTime = 0.0f;
			}
		}
		else
		{
			if (mMoveTime < 3.0f)
			{

				pos.x += 3.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

			}
			if (mMoveTime < 6.0f && mMoveTime > 3.0f)
			{

				pos.x -= 3.0f * Time::DeltaTime();
				mTr->SetPosition(pos);

			}

			if (mMoveTime >= 6.0f)
			{
				mMoveTime = 0.0f;
			}
		}

		if (mTime > 4.0f)
		{
			GameObject* bullet = object::CreateGameObject<GameObject>(eLayerType::MonsterAttack);
			Transform* tr = bullet->GetComponent<Transform>();
			tr->SetPosition((Vector3(mTr->GetPosition().x, mTr->GetPosition().y, 9.0f)));
			tr->SetScale(Vector3(8.0f, 8.0f, 1.0f));
			HelicopterBulletScript* scr = bullet->AddComponent<HelicopterBulletScript>();
			scr->SetPlayerPos(playerPos);
			scr->SetRot(mRot);
			mTime = 0.0f;
		}
	}
	void HelicopterScript::Die()
	{
	}
}