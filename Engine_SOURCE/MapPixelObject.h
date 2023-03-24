#pragma once
class MapPixelObject
{
};

#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Player;
	class MapPixelObject : public GameObject
	{
	public:
		union Pixel
		{
			struct
			{
				BYTE R;
				BYTE G;
				BYTE B;
				BYTE A;
			};
			DWORD Color;

			Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
				:R(r), G(g), B(b), A(a)
			{

			}

			Pixel(COLORREF color)
				:Color(color)
			{

			}

		};

		MapPixelObject();
		~MapPixelObject();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		Player* mPlayer;

	private:
		bool mbDebug;
		bool mGroundOX;
	};
}
