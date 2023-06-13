#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
		void CreateGameObject(GameObject* gameObject);
		const std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }
		std::vector<GameObject*> GetDontDestroyGameObjects();


	private:
		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mCreateGameObjects;
	};

	typedef const std::vector<GameObject*>& GameObjects;
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}
