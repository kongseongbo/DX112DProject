#include "yaMosqueArtilleryeHeadRightScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaAnimator.h"


namespace ya
{
	MosqueArtilleryeHeadRightScript::MosqueArtilleryeHeadRightScript()
		: Script()
		, stack(0)
		, mbStartAni(false)
	{
	}
	MosqueArtilleryeHeadRightScript::~MosqueArtilleryeHeadRightScript()
	{
	}
	void MosqueArtilleryeHeadRightScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryHeadRight", L"MosqueArtillery\\MosqueArtilleryeHeadRight.png");
		ani->Create(L"MosqueArtilleryHeadRight", texture, Vector2(0.0f, 0.0f), Vector2(88.0f, 139.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadRightOpen", L"MosqueArtillery\\MosqueArtilleryeHeadRightOpen.png");
		ani->Create(L"MosqueArtilleryHeadRightOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 16, 0.2f);
		ani->Create(L"RightCurtain", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);
		ani->Create(L"RightAttack", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);

		ani->GetCompleteEvent(L"MosqueArtilleryHeadRightOpen") = std::bind(&MosqueArtilleryeHeadRightScript::NewBoss, this);

		ani->Play(L"MosqueArtilleryHeadRight", false);
	}
	void MosqueArtilleryeHeadRightScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryHeadRightOpen", false);

			stack++;
		}
	}
	void MosqueArtilleryeHeadRightScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadRightScript::Render()
	{
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnTriggerExit(Collider2D* collider)
	{

	}
	void MosqueArtilleryeHeadRightScript::NewBoss()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"RightCurtain", false);
	}
}