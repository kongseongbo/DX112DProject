#include "yaCenterEffectScript.h"
#include "yaAnimator.h"
#include "yaResources.h"


namespace ya
{
	CenterEffectScript::CenterEffectScript()
		: Script()
		, mTr(nullptr)
		, mTime(0.0f)
	{
	}
	CenterEffectScript::~CenterEffectScript()
	{
	}
	void CenterEffectScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryAttackEffect", L"MosqueArtillery\\Effect.png");
		ani->Create(L"CenterAttackEffect", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 52.0f), Vector2(0.0f, 0.0f), 32, 0.2f);
	}
	void CenterEffectScript::Update()
	{
		if (scr->eState == MosqueArtilleryeHeadCenterScript::State::ATTCK)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"CenterAttackEffect", false);
		}
	}
	void CenterEffectScript::FixedUpdate()
	{
	}
	void CenterEffectScript::Render()
	{
	}
	void CenterEffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CenterEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CenterEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
}