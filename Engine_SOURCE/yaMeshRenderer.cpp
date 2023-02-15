#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenerer)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initalize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mMaterial->Bind();
		mMesh->BindBuffer();

		mMesh->Render();

		mMaterial->Clear();
	}
}
