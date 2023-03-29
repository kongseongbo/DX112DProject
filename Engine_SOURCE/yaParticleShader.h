#pragma once
#include "yaComputeShader.h"
#include "yaStructedBuffer.h"

namespace ya::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(StructedBuffer* buffer);

	private:
		StructedBuffer* mBuffer;
	};
}