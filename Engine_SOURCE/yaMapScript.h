#pragma once
#include "yaScript.h"

#include "yaPlayer.h"
#include "yaCameraScript.h"
#include "yaTheKeesiScript.h"


namespace ya
{
	class MapScript : public Script
	{
	public:
		MapScript();
		virtual ~MapScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void CreateArabian(Vector3 position);
		void CreateArabian1(Vector3 position);
		void CreateArabian2(Vector3 position);
		void CreateArabian3(Vector3 position);
		void CreateCamelArabian(Vector3 position);
		void CreateHelicopter(Vector3 position);
		void CreateThekeesi(Vector3 position);

		void MissionComplete();

		bool GetPlayerCamera() { return mbPlayerCamera; }
		void SetPlayerCamera(bool a) { mbPlayerCamera = a; }

		void SetPlayer(Player* player) { mPlayer = player; }
		void SetCamerarScript(CameraScript* scr) { cameraScript = scr; }
	
	
	private:
		Transform* mTr;

		Player* mPlayer;
		CameraScript* cameraScript;

		TheKeesiScript* mThekeesiScript;

		bool mbPlayerCamera;
		float mTime;
	};
}