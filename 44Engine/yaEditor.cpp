#include "yaEditor.h"
#include "yaMesh.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"

namespace ya
{
	void Editor::Initalize()
	{
		// 충돌체의 종류 갯수만큼만 있으면 된다.
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();

		MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();

		renderer->SetMesh(rectMesh);
		renderer->SetMaterial(material);

		std::shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");

		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<Transform>();
	
		renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

		renderer->SetMesh(circleMesh);
		renderer->SetMaterial(material);

		//그리드 이쪽으로 옮겨줘야 한다.
	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
	}

	void Editor::FixedUpdate()
	{
	}

	void Editor::Render()
	{
	}

	void Editor::Release()
	{
	}

	void Editor::DebugRender(graphics::DebugMesh& mehs)
	{
	}
}
