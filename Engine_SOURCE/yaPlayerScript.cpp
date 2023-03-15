#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaObject.h"

namespace ya
{
	PlayerScript::State PlayerScript::mState = State::IDLE;

	PlayerScript::PlayerScript()
		: Script()
		, mTr(nullptr)
	{
		
	}

	PlayerScript::~PlayerScript()
	{
	
	}

	void PlayerScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();;
		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);

		if (animator->GetName() == L"HeadIdle")
		{
			animator->GetCompleteEvent(L"HeadIdle") = std::bind(&PlayerScript::Action, this);
			animator->GetEndEvent(L"HeadIdle") = std::bind(&PlayerScript::End, this);
			animator->GetEvent(L"HeadIdle", 1) = std::bind(&PlayerScript::End, this);
		}

		if (animator->GetName() == L"BodyIdle")
		{
			animator->GetCompleteEvent(L"BodyIdle") = std::bind(&PlayerScript::Action, this);
			animator->GetEndEvent(L"BodyIdle") = std::bind(&PlayerScript::End, this);
			animator->GetEvent(L"BodyIdle", 1) = std::bind(&PlayerScript::End, this);
		}
	}

	void PlayerScript::Update()
	{
		switch (mState)
		{
		case ya::PlayerScript::State::IDLE:
			Idle();
			break;
		case ya::PlayerScript::State::LEFTMOVE:
			LeftMove();
			break;
		case ya::PlayerScript::State::RIGHTMOVE:
			RightMove();
			break;
		case ya::PlayerScript::State::HIT:
			Hit();
			break;
		case ya::PlayerScript::State::ATTACK:
			Attack();
			break;
		case ya::PlayerScript::State::SITDOWN:
			SitDown();
			break;
		case ya::PlayerScript::State::DEATH:
			Death();
			break;
		default:
			break;
		}


		//Transform* mTr = GetOwner()->GetComponent<Transform>();
		////Vector3 rot = tr->GetRotation();
		////rot.z += 10.0f * Time::DeltaTime();
		////tr->SetRotation(rot);
		//if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		//{
		//	Vector3 rot = mTr->GetRotation();
		//	rot.z += 10.0f * Time::DeltaTime();
		//	mTr->SetRotation(rot);
		//	Vector3 pos = mTr->GetPosition();
		//	pos.x += 10.0f * Time::DeltaTime();
		//	mTr->SetPosition(pos);
		//}
		//Animator* animator = GetOwner()->GetComponent<Animator>();
		//if (Input::GetKey(eKeyCode::N_1))
		//{
		//	animator->Play(L"MoveDown");
		//}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
	}

	void PlayerScript::Idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mState = State::RIGHTMOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mState = State::LEFTMOVE;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			
		}
	}

	void PlayerScript::LeftMove()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT))
			mState = State::IDLE;

		Vector3 pos = mTr->GetPosition();
		pos.x -= 6.0f * Time::DeltaTime();
		mTr->SetPosition(pos);
	}

	void PlayerScript::RightMove()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT))
			mState = State::IDLE;

		Vector3 pos = mTr->GetPosition();
		pos.x += 6.0f * Time::DeltaTime();
		mTr->SetPosition(pos);
	}

	void PlayerScript::Jump()
	{
	}

	void PlayerScript::SitDown()
	{
	}

	void PlayerScript::Attack()
	{
	}

	void PlayerScript::Hit()
	{
	}

	void PlayerScript::Death()
	{
	}
}