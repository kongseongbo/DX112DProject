#include "yaPlayerBodyAni.h"
#include "yaResources.h"
#include "yaGameObject.h"




namespace ya
{
	PlayerBodyAni::PlayerBodyAni()
		:Script()
	{
	}
	PlayerBodyAni::~PlayerBodyAni()
	{
	}
	void PlayerBodyAni::Initalize()
	{
		bodyAni = GetOwner()->GetComponent<BodyAnimator>();
		mPlayerScript = GetOwner()->GetScript<PlayerScript>();

		std::shared_ptr<Texture> bodyidle = Resources::Load<Texture>(L"bodyidle", L"Character\\Marco\\IdleD.png");
		bodyAni->Create(L"BodyIdle", bodyidle, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

		std::shared_ptr<Texture> MoveLeftD = Resources::Load<Texture>(L"MoveLeftD", L"Character\\Marco\\LMoveD.png");
		bodyAni->Create(L"MoveLeftD", MoveLeftD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

		std::shared_ptr<Texture> MoveRightD = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
		bodyAni->Create(L"MoveRightD", MoveRightD, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

		mPlayerScript->SetBodyAnimator(bodyAni);
	}
	void PlayerBodyAni::Update()
	{
	}
	void PlayerBodyAni::Render()
	{
	}
}