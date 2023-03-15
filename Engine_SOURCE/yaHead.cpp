#include "yaHead.h"
#include "yaComponent.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaPlayerScript.h"

namespace ya
{
	Head::Head()
		: mAnimator(nullptr)
	{
		
	}

	Head::~Head()
	{
	}

	void Head::Initalize()
	{
		
		mAnimator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Character\\Marco\\IdleU.png");
		mAnimator->Create(L"HeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 36.0f), Vector2::Zero, 4, 0.3f);
		mAnimator->Play(L"HeadIdle", true);

		
	}

	void Head::Update()
	{
		if(PlayerScript::mState !=PlayerScript::State::IDLE)
			mAnimator->Play(L"HeadIdle", false);

	}

	void Head::FixedUpdate()
	{

	}

	void Head::Render()
	{
	}

}
