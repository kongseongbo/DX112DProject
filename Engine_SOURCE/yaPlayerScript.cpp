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
	PlayerScript::HeadState PlayerScript::mHeadState = HeadState::IDLE;
	PlayerScript::BodyState PlayerScript::mBodyState = BodyState::IDLE;

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

		if(GetOwner()->GetName() == L"Head")
			headAni = GetOwner()->GetComponent<Animator>();

		if (headAni != nullptr && bodyAni != nullptr)
		{
			std::shared_ptr<Texture> bodyidle = Resources::Load<Texture>(L"bodyidle", L"Character\\Marco\\IdleD.png");
			bodyAni->Create(L"BodyIdle", bodyidle, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			std::shared_ptr<Texture> headIdle = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
			headAni->Create(L"HeadIdle", headIdle, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			std::shared_ptr<Texture> MoveLeftU = Resources::Load<Texture>(L"MoveLeftU", L"Character\\Marco\\LMoveU.png");
			headAni->Create(L"MoveLeftU", MoveLeftU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> MoveLeftD = Resources::Load<Texture>(L"MoveLeftD", L"Character\\Marco\\LMoveD.png");
			bodyAni->Create(L"MoveLeftD", MoveLeftD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> MoveRightU = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			headAni->Create(L"MoveRightU", MoveRightU, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> MoveRightD = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
			bodyAni->Create(L"MoveRightD", MoveRightD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			std::shared_ptr<Texture> PistolAttackU = Resources::Load<Texture>(L"PistolAttackU", L"Character\\Marco\\PistolAttackU.png");
			headAni->Create(L"PistolAttackU", PistolAttackU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.1f);

			std::shared_ptr<Texture> LPistolAttackU = Resources::Load<Texture>(L"LPistolAttackU", L"Character\\Marco\\LPistolAttackU.png");
			headAni->Create(L"LPistolAttackU", LPistolAttackU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.1f);
			
			headAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&PlayerScript::End, this);
		}
		           
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
		

		switch (mHeadState)
		{
		case ya::PlayerScript::HeadState::IDLE:
			
			Idle();
			break;
		case ya::PlayerScript::HeadState::MOVE:
			Move();
			break;
		case ya::PlayerScript::HeadState::HIT:
			Hit();
			break;
		case ya::PlayerScript::HeadState::ATTACK:
			Attack();
			break;
		case ya::PlayerScript::HeadState::SITDOWN:
			SitDown();
			break;
		case ya::PlayerScript::HeadState::DEATH:
			Death();
			break;
		default:
			break;
		}

		headState = mHeadState;

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
		headAni->Play(L"HeadIdle", true);
	}

	void PlayerScript::Idle()
	{

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::LEFT))
		{
			mHeadState = HeadState::MOVE;
			mBodyState = BodyState::MOVE;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			mHeadState = HeadState::ATTACK;
		}

		if (headState == mHeadState)
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
		{
			mHeadState = HeadState::IDLE;
			mBodyState = BodyState::IDLE;
			return;
		}
		mHeadState = HeadState::MOVE;
		mBodyState = BodyState::MOVE;

		Vector3 pos = mTr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			if (headState == mHeadState)
				return;

			if (headAni != nullptr && bodyAni != nullptr)
			{
				Transform* headPos = mHeadPlayer->GetComponent<Transform>();
				Transform* bodyPos = mHeadPlayer->GetComponent<Transform>();
				//bodyPos->SetPosition(Vector3(headPos->GetPosition().x - 1.2f, headPos->GetPosition().y - 1.3f, 5.0f));

				PositionSetting(headPos, bodyPos);
				headAni->Play(L"MoveLeftU", true);
				bodyAni->Play(L"MoveLeftD", true);
			}
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			//headAni->Play(L"PistolAttackU", false);
			mHeadState = HeadState::ATTACK;
		}
			
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
				
			if (headState == mHeadState)
				return;

			if (headAni != nullptr && bodyAni != nullptr && (mHeadState == HeadState::MOVE))
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
		Vector3 pos = mTr->GetPosition();
		pos.x += 6.0f * Time::DeltaTime();
		if (headState == mHeadState)
			return;
		
		
		if (headAni != nullptr && bodyAni != nullptr)
		{
			headAni->Play(L"PistolAttackU", false);

			if (mBodyState == BodyState::IDLE)
			{
				bodyAni->Play(L"BodyIdle", true);
				mHeadState = HeadState::IDLE;
			}
				
			if (mBodyState == BodyState::MOVE)
			{
				
				mTr->SetPosition(pos);

				bodyAni->Play(L"MoveRightD", true);
			}
		}
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