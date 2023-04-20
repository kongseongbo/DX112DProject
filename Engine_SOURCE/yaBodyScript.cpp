#include "yaBodyScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaBody.h"
#include "yaCollider2D.h"
#include "yaHeadScript.h"

namespace ya
{
	BodyScript::BodyScript()
		: Script()
		, mTr(nullptr)
		, bodyAni(nullptr)
		, direction(0)
	{
		mBodyState = BodyState::IDLE;
	}

	BodyScript::~BodyScript()
	{

	}

	void BodyScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		bodyAni = GetOwner()->GetComponent<Animator>();
		if (bodyAni != nullptr)
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bodyidle", L"Character\\Marco\\IdleD.png");
			bodyAni->Create(L"BodyIdle", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			texture = Resources::Load<Texture>(L"Lbodyidle", L"Character\\Marco\\LIdleD.png");
			bodyAni->Create(L"LBodyIdle", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			texture = Resources::Load<Texture>(L"MoveLeftD", L"Character\\Marco\\LMoveD.png");
			bodyAni->Create(L"MoveLeftD", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			texture = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
			bodyAni->Create(L"MoveRightD", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			texture = Resources::Load<Texture>(L"JumpD", L"Character\\Marco\\JumpD.png");
			bodyAni->Create(L"JumpD", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2(-0.01f, 0.19f), 6, 0.1f);
			bodyAni->Create(L"LJumpD", texture, Vector2(0.0f, 30.0f), Vector2(30.0f, 30.0f), Vector2(-0.028f, 0.19f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"JumpMoveD", L"Character\\Marco\\JumpMoveD.png");
			bodyAni->Create(L"JumpMoveD", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 24.0f), Vector2(-0.04f, 0.0f), 6, 0.1f);
			bodyAni->Create(L"LJumpMoveD", texture, Vector2(0.0f, 24.0f), Vector2(40.0f, 24.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);

			// 투명이미지
			texture = Resources::Load<Texture>(L"def", L"Character\\Marco\\def.png");
			bodyAni->Create(L"def", texture, Vector2(0.0f, 50.f), Vector2(50.0f, 50.0f), Vector2::Zero, 1, 0.1f);

			bodyAni->Play(L"BodyIdle", true);

		}
	}

	void BodyScript::Update()
	{
		Transform* headTr = mHead->GetComponent<Transform>();
		Vector3 headPos = headTr->GetPosition();
		mTr->SetPosition(Vector3(headTr->GetPosition().x - 0.2f, headTr->GetPosition().y - 1.3f, 5.0f));

		bodyAni = GetOwner()->GetComponent<Animator>();
		switch (mBodyState)
		{
		case ya::BodyState::IDLE:
			Idle();
			break;
		case ya::BodyState::MOVE:
			Move();
			break;
		case ya::BodyState::JUMP:
			Jump();
			break;
		case ya::BodyState::HIT:
			Hit();
			break;
		case ya::BodyState::ATTACK:
			Attack();
			break;
		case ya::BodyState::SITDOWN:
			SitDown();
			break;
		case ya::BodyState::SITDOWNMOVE:
			SitDownMove();
			break;
		//case ya::BodyScript::BodyState::SITDOWNATTACK:
		//	SitDownAttack();
		//	break;
		case ya::BodyState::DEATH:
			Death();
			break;
		default:
			break;
		}



	}

	void BodyScript::Render()
	{
	}

	void BodyScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mBodyState == BodyState::JUMP&& direction == 0)
		{
			bodyAni->Play(L"BodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		else if (mBodyState == BodyState::JUMP && direction == 1)
		{
			bodyAni->Play(L"LBodyIdle", true);
			mBodyState = BodyState::IDLE;
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::MonsterAttack)
		{
			if (mBodyState == BodyState::DEATH)
				return;

			bodyAni->Play(L"def", true);
			mBodyState = BodyState::DEATH;
		}


	}

	void BodyScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void BodyScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void BodyScript::Start()
	{
	}

	void BodyScript::Action()
	{
	}

	void BodyScript::End()
	{
		
	}

	void BodyScript::Idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			direction = 0;
			bodyAni->Play(L"MoveRightD", true);
			mBodyState = BodyState::MOVE;
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			direction = 1;
			bodyAni->Play(L"MoveLeftD", true);
			mBodyState = BodyState::MOVE;
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			bodyAni->Play(L"def", true);
			mBodyState = BodyState::SITDOWN;
		}

		if (Input::GetKey(eKeyCode::SPACE) && direction == 0)
		{
			bodyAni->Play(L"JumpD", false);
			mBodyState = BodyState::JUMP;
		}
		else if (Input::GetKey(eKeyCode::SPACE) && direction == 1)
		{
			bodyAni->Play(L"LJumpD", false);
			mBodyState = BodyState::JUMP;
		}
	}

	void BodyScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			direction = 0;
			bodyAni->Play(L"BodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			direction = 1;
			bodyAni->Play(L"LBodyIdle", true);
			mBodyState = BodyState::IDLE;
		}

		if (Input::GetKey(eKeyCode::DOWN) && direction == 0)
		{
			bodyAni->Play(L"def", false);
			mBodyState = BodyState::SITDOWN;
		}
		else if (Input::GetKey(eKeyCode::DOWN) && direction == 1)
		{
			bodyAni->Play(L"def", false);
			mBodyState = BodyState::SITDOWN;
		}

		if (Input::GetKey(eKeyCode::SPACE) && direction == 0)
		{
			bodyAni->Play(L"JumpMoveD", false);
			mBodyState = BodyState::JUMP;
		}
		else if (Input::GetKey(eKeyCode::SPACE) && direction == 1)
		{
			bodyAni->Play(L"LJumpMoveD", false);
			mBodyState = BodyState::JUMP;
		}
	}

	void BodyScript::Jump()
	{



	}

	void BodyScript::SitDown()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 0)
		{
			bodyAni->Play(L"BodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 1)
		{
			bodyAni->Play(L"LBodyIdle", true);
			mBodyState = BodyState::IDLE;
		}

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::LEFT))
			mBodyState = BodyState::SITDOWNMOVE;

	}

	void BodyScript::SitDownMove()
	{
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			direction = 0;
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			direction = 1;
		}

		if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 0)
		{
			bodyAni->Play(L"BodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 1)
		{
			bodyAni->Play(L"LBodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		
	}

	void BodyScript::SitDownAttack()
	{
	}

	void BodyScript::Attack()
	{

	}

	void BodyScript::Hit()
	{
	}

	void BodyScript::Death()
	{
		if (GetOwner()->GetState() == GameObject::Active)
		{
			if (mHeadState == HeadState::NONE)
			{
				
				//bodyAni->Play(L"BodyIdle", true);
				mBodyState = BodyState::IDLE;
			}
		}
		
		else
			GetOwner()->Pause();
	}
}
