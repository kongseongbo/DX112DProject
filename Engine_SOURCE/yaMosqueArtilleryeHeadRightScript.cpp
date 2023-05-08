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
		, mbStartAni(false)
	{
	}
	MosqueArtilleryeHeadRightScript::~MosqueArtilleryeHeadRightScript()
	{
	}
	void MosqueArtilleryeHeadRightScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		//std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryMoon", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		//ani->Create(L"MosqueArtilleryeHeadCenterOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, 0.0f), 16, 0.2f);

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadRight", L"MosqueArtillery\\MosqueArtilleryeHeadRight.png");
		ani->Create(L"MosqueArtilleryeHeadRight", texture, Vector2(0.0f, 0.0f), Vector2(88.0f, 139.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		ani->Play(L"MosqueArtilleryeHeadRight", false);
	}
	void MosqueArtilleryeHeadRightScript::Update()
	{
	
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
}