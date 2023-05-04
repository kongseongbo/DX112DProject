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
	{
	}
	MosqueArtilleryeHeadCenterScript::~MosqueArtilleryeHeadCenterScript()
	{
	}
	void MosqueArtilleryeHeadCenterScript::Initalize()
	{
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"mosqueArtilleryCenterMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);
	}
	void MosqueArtilleryeHeadCenterScript::Update()
	{
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