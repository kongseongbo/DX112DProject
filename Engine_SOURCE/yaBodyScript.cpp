#include "yaBodyScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaBody.h"
#include "yaHead.h"

namespace ya
{
	BodyScript::BodyState BodyScript::mBodyState = BodyState::IDLE;

	BodyScript::BodyScript()
		: Script()
		, mTr(nullptr)
		, bodyAni(nullptr)
		, direction(0)
	{

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
		case ya::BodyScript::BodyState::IDLE:
			Idle();
			break;
		case ya::BodyScript::BodyState::MOVE:
			Move();
			break;
		case ya::BodyScript::BodyState::JUMP:
			Jump();
			break;
		case ya::BodyScript::BodyState::HIT:
			Hit();
			break;
		case ya::BodyScript::BodyState::ATTACK:
			Attack();
			break;
		case ya::BodyScript::BodyState::SITDOWN:
			SitDown();
			break;
		//case ya::BodyScript::BodyState::SITDOWNMOVE:
		//	SitDownMove();
		//	break;
		//case ya::BodyScript::BodyState::SITDOWNATTACK:
		//	SitDownAttack();
		//	break;
		case ya::BodyScript::BodyState::DEATH:
			Death();
			break;
		default:
			break;
		}

		bodyState = mBodyState;

	}

	void BodyScript::Render()
	{
	}

	void BodyScript::OnCollisionEnter(Collider2D* collider)
	{

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
			bodyAni->Play(L"MoveRightD", true);
			mBodyState = BodyState::MOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			bodyAni->Play(L"MoveLeftD", true);
			mBodyState = BodyState::MOVE;
		}
	}

	void BodyScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			bodyAni->Play(L"BodyIdle", true);
			mBodyState = BodyState::IDLE;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			bodyAni->Play(L"LBodyIdle", true);
			mBodyState = BodyState::IDLE;
		}


	}

	void BodyScript::Jump()
	{



	}

	void BodyScript::SitDown()
	{

	}

	void BodyScript::SitDownMove()
	{


		
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
	}
}
