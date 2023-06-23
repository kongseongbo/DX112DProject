#include "yaGoUiScript.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaInput.h"


namespace ya
{
	GoUiScript::GoUiScript()
		: Script()
		, mTime(0.0f)
		, mbGo(false)
	{
	}
	GoUiScript::~GoUiScript()
	{
	}
	void GoUiScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Go", L"Go.png");
		ani->Create(L"Go", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 33.0f), Vector2(0.0f, 0.0f), 17, 0.2f);

		texture = Resources::Load<Texture>(L"def", L"Character\\Marco\\def.png");
		ani->Create(L"xxx", texture, Vector2(0.0f, 50.f), Vector2(50.0f, 50.0f), Vector2::Zero, 1, 0.1f);

		ani->GetCompleteEvent(L"Go") = std::bind(&GoUiScript::End, this);
	}
	void GoUiScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (!Input::GetKey(eKeyCode::RIGHT))
		{
			mTime += 2.0f * Time::DeltaTime();
		}
		
		if (mTime > 5.0f)
		{

			if (!Input::GetKey(eKeyCode::RIGHT))
			{
				mbGo = false;
			}
			
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mbGo = true;
			}
			if (!mbGo)
			{
				if (!ani->IsAnimationRunning(L"Go"))
					ani->Play(L"Go", false);
			}
			mTime = 0.0f;
		}
		
		

	}
	void GoUiScript::FixedUpdate()
	{
	}
	void GoUiScript::Render()
	{
	}
	void GoUiScript::End()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"xxx", false);
	}
}