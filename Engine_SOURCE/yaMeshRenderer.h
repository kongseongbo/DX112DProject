#pragma once
#include "yaComponent.h"
#include "yaMesh.h"
#include "yaMaterial.h"

using namespace ya::graphics;
namespace ya
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> shader) { mMaterial = shader; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}