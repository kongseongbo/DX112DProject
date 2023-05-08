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
	{
	}
	MosqueArtilleryeHeadLeftScript::~MosqueArtilleryeHeadLeftScript()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		//std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryMoon", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		//ani->Create(L"MosqueArtilleryeHeadCenterOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, 0.0f), 16, 0.2f);

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadLeft", L"MosqueArtillery\\MosqueArtilleryeHeadLeft.png");
		ani->Create(L"MosqueArtilleryeHeadLeft", texture, Vector2(0.0f, 0.0f), Vector2(89.0f, 138.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		ani->Play(L"MosqueArtilleryeHeadLeft", false);
	}
	void MosqueArtilleryeHeadLeftScript::Update()
	{
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
}