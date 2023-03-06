#pragma once
#include "CommonInclude.h"
#include "yaCollider2D.h"

namespace ya
{
	union ClooiderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id; // left�� right�� ��� �������ִ� ����
	};

	class CollisionManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);

	private:
		static std::bitset<(UINT)eLayerType::End> mLayerCollisionMatrix[(UINT)eLayerType::End]; //1bit�� ���
		static std::map<UINT64, bool> mColliderMap;

	};

}