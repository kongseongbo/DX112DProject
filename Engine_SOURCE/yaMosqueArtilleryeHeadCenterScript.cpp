#include "yaMosqueArtilleryeHeadCenterScript.h"
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
	MosqueArtilleryeHeadCenterScript::MosqueArtilleryeHeadCenterScript()
		: Script()
		, mbStartAni(false)
		, stack(0)
	{
	}
	MosqueArtilleryeHeadCenterScript::~MosqueArtilleryeHeadCenterScript()
	{
	}
	void MosqueArtilleryeHeadCenterScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadCenter", L"MosqueArtillery\\MosqueArtilleryeHeadCenter.png");
		ani->Create(L"MosqueArtilleryeHeadCenter", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 138.0f), Vector2(0.0f, 0.0f), 1, 0.2f);
		
		texture = Resources::Load<Texture>(L"MosqueArtilleryMoon", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		ani->Create(L"MosqueArtilleryeHeadCenterOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f,-0.035f), 16, 0.2f);

		ani->Play(L"MosqueArtilleryeHeadCenter", false);
	}
	void MosqueArtilleryeHeadCenterScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		SpriteRenderer* sr = GetOwner()->GetComponent<SpriteRenderer>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryeHeadCenterOpen", false);
			stack++;
		}
	}
	void MosqueArtilleryeHeadCenterScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadCenterScript::Render()
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnTriggerExit(Collider2D* collider)
	{
	}
}