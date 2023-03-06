#include "yaCollisionManager.h"



namespace ya
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mColliderMap;

	void CollisionManager::Initalize()
	{
	}
	void CollisionManager::Update()
	{
	}
	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int coIumn = 0;

	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
	}
}