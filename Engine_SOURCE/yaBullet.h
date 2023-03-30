#include "yaGameObject.h"



namespace ya
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		 ~Bullet();

		void Initalize();
		void Update();
		void FixedUpdate();
		void Render();

		void Attack();

		void SetPlayer(GameObject* player) { mPlayer = player; }

	private:
		GameObject* mPlayer;

	};
}