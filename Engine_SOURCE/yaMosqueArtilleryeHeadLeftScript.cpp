#include "yaMosqueArtilleryeHeadLeftScript.h"
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
	MosqueArtilleryeHeadLeftScript::MosqueArtilleryeHeadLeftScript()
		: Script()
		, mbStartAni(false)
		, stack(0)
	{
	}
	MosqueArtilleryeHeadLeftScript::~MosqueArtilleryeHeadLeftScript()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadLeft", L"MosqueArtillery\\MosqueArtilleryeHeadLeft.png");
		ani->Create(L"MosqueArtilleryeHeadLeft", texture, Vector2(0.0f, 0.0f), Vector2(89.0f, 138.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadLeftOpen", L"MosqueArtillery\\MosqueArtilleryeHeadLeftOpen.png");
		ani->Create(L"MosqueArtilleryeHeadLeftOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 16, 0.2f);
		ani->Create(L"LeftCurtain", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);
		ani->Create(L"LeftAttack", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);

		ani->GetCompleteEvent(L"MosqueArtilleryeHeadLeftOpen") = std::bind(&MosqueArtilleryeHeadLeftScript::NewBoss, this);

		ani->Play(L"MosqueArtilleryeHeadLeft", false);
	}
	void MosqueArtilleryeHeadLeftScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryeHeadLeftOpen", false);

			stack++;
		}
	}
	void MosqueArtilleryeHeadLeftScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Render()
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::NewBoss()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"LeftCurtain", false);
	}
}