#include "yaDeathEffect.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"

namespace ya
{
	DeathEffect::DeathEffect()
		: Script()
		, ox(false)
	{
	}
	DeathEffect::~DeathEffect()
	{
	}
	void DeathEffect::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture>texture = Resources::Load<Texture>(L"DeathEffect", L"Helicopter\\DeathEffect.png");
		ani->Create(L"DeathEffect", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 56.0f), Vector2(0.01f, 0.0f), 6, 0.2f);

		ani->Play(L"DeathEffect", true);


		ani->GetCompleteEvent(L"DeathEffect") = std::bind(&DeathEffect::End, this);
	}
	void DeathEffect::Update()
	{
		
		

	}
	void DeathEffect::FixedUpdate()
	{
	}
	void DeathEffect::Render()
	{
	}
	void DeathEffect::End()
	{
		mTime += 0.5 * Time::DeltaTime();

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> distr(0, 3);
		
		if (!ox)
		{
			mTr->SetPosition(Vector3(mTr->GetPosition().x + distr(eng), mTr->GetPosition().y - mTime, mTr->GetPosition().z));
			ox = true;
		}
		if (ox)
		{
			mTr->SetPosition(Vector3(mTr->GetPosition().x - distr(eng), mTr->GetPosition().y - mTime, mTr->GetPosition().z));
			ox = false;
		}
	}
}