#pragma once

namespace ya::enums
{


	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Map,
		Monster,
		Player,

		UI,
		FadeIn,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, 
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

}