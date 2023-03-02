#pragma once
#include "yaDebugObject.h"
#include "yaEditorObject.h"
#include "yaWidget.h"


namespace ya
{
	class Editor
	{
	public:
		void Initalize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender();

	private:
		std::vector<Widget> mWidgets;
		std::vector<EditorObject> mEditorObjects;
		std::vector<DebugObject> mDebugObjects;


	};
}