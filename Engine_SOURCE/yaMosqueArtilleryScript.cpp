#include "yaMosqueArtilleryScript.h"
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
	MosqueArtilleryScript::MosqueArtilleryScript()
		: Script()
		, mbSpriteChange(false)
	{
	}
	MosqueArtilleryScript::~MosqueArtilleryScript()
	{
	}
	void MosqueArtilleryScript::Initalize()
	{

		//mosqueArtilleryDestroyMaterial

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"mosqueArtilleryBaseMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(heliMaterial);
		sr->SetMesh(mesh);


	}
	void MosqueArtilleryScript::Update()
	{
		if (mbSpriteChange)
		{
			SpriteRenderer* sr = GetOwner()->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"mosqueArtilleryDestroyMaterial");
			sr->SetMaterial(heliMaterial);
		}
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