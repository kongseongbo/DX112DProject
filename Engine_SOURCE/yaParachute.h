#include "yaGameObject.h"



namespace ya
{
	class Parachute : public GameObject
	{
	public:
		Parachute();
		virtual ~Parachute();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};
}