#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
//#include "yaPlayer.h"
#include "yaObject.h"

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

		if (headAni != nullptr)
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Character\\Marco\\IdleU.png");
			headAni->Create(L"HeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 36.0f), Vector2::Zero, 4, 0.3f);
			headAni->Play(L"HeadIdle", true);
		}

		if (bodyAni != nullptr)
		{
			std::shared_ptr<Texture> bodyTexture = Resources::Load<Texture>(L"Zelda1", L"Character\\Marco\\IdleD.png");
			bodyAni->Create(L"BodyIdle", bodyTexture, Vector2(0.0f, 0.0f), Vector2(33.0f, 36.0f), Vector2::Zero, 1, 0.3f);
			bodyAni->Play(L"BodyIdle", true);
		}
	}

	void PlayerScript::Move()
	{

		
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
			mState = State::IDLE;

		Vector3 pos = mTr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 6.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 6.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		if (prevState == mState)
			return;
		if (headAni != nullptr)
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			headAni->Create(L"MoveRightU", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);
			headAni->Play(L"MoveRightU", true);
		}

		if (bodyAni != nullptr)
		{
			/*Transform* bodyPos = mBodyPlayer->GetComponent<Transform>();
			bodyPos->SetPosition(Vector3(bodyPos->GetPosition().x, bodyPos->GetPosition().y - 0.5, 1.0f));*/
			std::shared_ptr<Texture> bodyTexture = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
			bodyAni->Create(L"MoveRightD", bodyTexture, Vector2(0.0f, 0.0f), Vector2(35.0f, 26.0f), Vector2::Zero, 12, 0.15f);
			bodyAni->Play(L"MoveRightD", true);
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

}