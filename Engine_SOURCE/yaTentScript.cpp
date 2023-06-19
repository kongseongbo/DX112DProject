#include "yaTentScript.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaCollider2D.h"

namespace ya
{
	

	TentScript::TentScript()
		: Script()
	{
	}
	TentScript::~TentScript()
	{
	}
	void TentScript::Initalize()
	{
		if (!(GetOwner()->GetName() == L"Tent"))
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"RightTent", L"Map\\RightTent.png");
			ani->Create(L"RightTent", texture, Vector2(360.0f, 60.0f), Vector2(90.0f, 60.0f), Vector2::Zero, 3, 0.1f);

			texture = Resources::Load<Texture>(L"RightTent", L"Map\\RightTent.png");
			ani->Create(L"ColliderTent", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 60.0f), Vector2::Zero, 4, 0.1f);

			ani->GetCompleteEvent(L"ColliderTent") = std::bind(&TentScript::End, this);

			ani->Play(L"RightTent", true);
		}
		mbOnColl = false;
	}
	void TentScript::Update()
	{
		if (!(GetOwner()->GetName() == L"Tent"))
		{
			if (mbOnColl)
			{
				Animator* ani = GetOwner()->GetComponent<Animator>();
				ani->Play(L"ColliderTent", false);
				mbOnColl = false;
			}
		}
	}
	void TentScript::FixedUpdate()
	{
	}
	void TentScript::Render()
	{
	}
	void TentScript::OnCollisionEnter(Collider2D* collider)
	{
		mbOnColl = true;
		
		
	}
	void TentScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TentScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void TentScript::End()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"RightTent", true);
	}
}