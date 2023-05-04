#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaBody.h"
#include "yaMapScript.h"
namespace ya
{

	class Stage1Scene : public Scene
	{
	public:
		Stage1Scene();
		virtual ~Stage1Scene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		
	private:
		GameObject* mCameraObj;
		Player* headObj;
		Body* bodyObj;
		MapScript* mapScript;

		Transform* mMosqueArtilleryleftTr;
		Transform* mMosqueArtilleryrightTr;
		Transform* mMosqueArtillerycenterTr;


		float mTime;
		float mZoom;
	};
}