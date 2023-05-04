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
	{
	}
	MosqueArtilleryeHeadLeftScript::~MosqueArtilleryeHeadLeftScript()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Initalize()
	{
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"mosqueArtilleryLeftMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);
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