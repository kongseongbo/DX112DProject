#pragma once
#include "..\Editor_SOURCE\yaDebugObject.h"
#include "..\Editor_SOURCE\yaEditorObject.h"
#include "..\Editor_SOURCE\yaWidget.h"


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