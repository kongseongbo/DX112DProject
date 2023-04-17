#include "yaMosqueArtilleryScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"



namespace ya
{
	MosqueArtilleryScript::MosqueArtilleryScript()
		: Script()
	{
	}
	MosqueArtilleryScript::~MosqueArtilleryScript()
	{
	}
	void MosqueArtilleryScript::Initalize()
	{
		SpriteRenderer* heliSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"mosqueArtilleryBaseMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		heliSr->SetMaterial(heliMaterial);
		heliSr->SetMesh(mesh);


	}
	void MosqueArtilleryScript::Update()
	{
	}
	void MosqueArtilleryScript::FixedUpdate()
	{
	}
	void MosqueArtilleryScript::Render()
	{
	}
	void MosqueArtilleryScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryScript::OnTriggerExit(Collider2D* collider)
	{
	}
}