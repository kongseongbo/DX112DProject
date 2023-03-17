#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaAnimation.h"

namespace ya
{
	PlayerScript::State PlayerScript::mState = State::IDLE;

	PlayerScript::PlayerScript()
		: Script()
		, mTr(nullptr)
		, headAni(nullptr)
		, mHeadPlayer(nullptr)
		, mBodyPlayer(nullptr)
	{
		
	}

	PlayerScript::~PlayerScript()
	{
	
	}

	void PlayerScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		if (headAni != nullptr && bodyAni != nullptr)
		{
			std::shared_ptr<Texture> bodyidle = Resources::Load<Texture>(L"bodyidle", L"Character\\Marco\\IdleD.png");
			bodyAni->Create(L"BodyIdle", bodyidle, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			std::shared_ptr<Texture> headIdle = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
			headAni->Create(L"HeadIdle", headIdle, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			std::shared_ptr<Texture> LMoveRightU = Resources::Load<Texture>(L"LMoveRightU", L"Character\\Marco\\LMoveU.png");
			headAni->Create(L"LMoveRightU", LMoveRightU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> LMoveRightD = Resources::Load<Texture>(L"LMoveRightD", L"Character\\Marco\\LMoveD.png");
			bodyAni->Create(L"LMoveRightD", LMoveRightD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> MoveRightU = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			headAni->Create(L"MoveRightU", MoveRightU, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> MoveRightD = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
			bodyAni->Create(L"MoveRightD", MoveRightD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);
		}
		//mState = State::IDLE;
		           
		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		/*if (animator->GetName() == L"HeadIdle")
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
		}*/
	}

	void PlayerScript::Update()
	{
		

		switch (mState)
		{
		case ya::PlayerScript::State::IDLE:
			
			Idle();
			break;
		case ya::PlayerScript::State::MOVE:
			Move();
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
		
		prevState = mState;

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
			mState = State::MOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mState = State::MOVE;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			
		}
		if (prevState == mState)
			return;

		if (bodyAni != nullptr)
		{
			bodyAni->Play(L"BodyIdle", true);
		}
		if (headAni != nullptr)
		{
			headAni->Play(L"HeadIdle", true);
		}

	}

	void PlayerScript::Move()
	{
		

		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
			mState = State::IDLE;
			
		

		Vector3 pos = mTr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			if (prevState == mState)
				return;

			if (headAni != nullptr && bodyAni != nullptr)
			{
				Transform* headPos = mHeadPlayer->GetComponent<Transform>();
				Transform* bodyPos = mHeadPlayer->GetComponent<Transform>();
				//bodyPos->SetPosition(Vector3(headPos->GetPosition().x - 1.2f, headPos->GetPosition().y - 1.3f, 5.0f));

				PositionSetting(headPos, bodyPos);
				headAni->Play(L"LMoveRightU", true);
				bodyAni->Play(L"LMoveRightD", true);

				
			}
		}
		
			
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
				
			if (prevState == mState)
				return;

			if (headAni != nullptr && bodyAni != nullptr)
			{
				headAni->Play(L"MoveRightU", true);
				bodyAni->Play(L"MoveRightD", true);
			}
		}
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

	void PlayerScript::PositionSetting(Transform* playerA, Transform* playerB)
	{
		////bodyPos->SetPosition(Vector3(headPos->GetPosition().x - 1.2f, headPos->GetPosition().y - 1.3f, 5.0f));

		////Transform* aTr = playerA->GetComponent<Transform>();
		//Vector3 aPos = playerA->GetPosition();

		////Transform* bTr = playerA->GetComponent<Transform>();
		//Vector3 bPos = playerB->GetPosition();

		//aPos.x -= 1.0f;

		//playerB->SetPosition(Vector3(aPos.x, bPos.y, bPos.z));
		
	}

}