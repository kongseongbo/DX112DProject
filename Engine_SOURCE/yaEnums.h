#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		CharacterSelect,
		Stage1,
		Stage1Boss,
		Stage2,
		Stage2Boss,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Map,
		Monster,
		Player,
		Animator,
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
		Animator,
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

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

}