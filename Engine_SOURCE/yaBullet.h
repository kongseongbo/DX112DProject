#include "yaGameObject.h"

namespace ya
{
	class Bullet/* : public GameObject*/
	{
	public:
		Bullet();
		 ~Bullet();

		void Initalize();
		void Update();
		void FixedUpdate();
		void Render();

	private:
	

	};
}