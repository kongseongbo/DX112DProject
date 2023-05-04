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
	{
	}
	MosqueArtilleryeHeadRightScript::~MosqueArtilleryeHeadRightScript()
	{
	}
	void MosqueArtilleryeHeadRightScript::Initalize()
	{
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"mosqueArtilleryRightMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);
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