#include "yaPlayerHeadAni.h"
#include "yaResources.h"
#include "yaGameObject.h"




namespace ya
{
	PlayerHeadAni::PlayerHeadAni()
	{
	}
	PlayerHeadAni::~PlayerHeadAni()
	{
	}
	void PlayerHeadAni::Initalize()
	{
		headAni = GetOwner()->GetComponent<Animator>();
		mPlayerScript = GetOwner()->GetScript<PlayerScript>();

		std::shared_ptr<Texture> headIdle = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
		headAni->Create(L"HeadIdle", headIdle, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

		std::shared_ptr<Texture> MoveLeftU = Resources::Load<Texture>(L"MoveLeftU", L"Character\\Marco\\LMoveU.png");
		headAni->Create(L"MoveLeftU", MoveLeftU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 12, 0.15f);

		std::shared_ptr<Texture> MoveRightU = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
		headAni->Create(L"MoveRightU", MoveRightU, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);

		std::shared_ptr<Texture> PistolAttackU = Resources::Load<Texture>(L"PistolAttackU", L"Character\\Marco\\PistolAttackU.png");
		headAni->Create(L"PistolAttackU", PistolAttackU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.1f);

		std::shared_ptr<Texture> LPistolAttackU = Resources::Load<Texture>(L"LPistolAttackU", L"Character\\Marco\\LPistolAttackU.png");
		headAni->Create(L"LPistolAttackU", LPistolAttackU, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.1f);

		mPlayerScript->SetHeadAnimator(headAni);
		//headAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&PlayerScript::End, this);
	}
	void PlayerHeadAni::Update()
	{
	}
	void PlayerHeadAni::Render()
	{
	}
}