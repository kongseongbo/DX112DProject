#include "yaParticleShader.h"
#include "yaRenderer.h"
#include "yaConstantBuffer.h"
#include "yaTime.h"

namespace ya::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mBuffer(nullptr)
	{
	}

	ParticleShader::~ParticleShader()
	{
	}

	void ParticleShader::Binds()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);

		mGroupX = mBuffer->GetStride() / mThreadGroupCountX;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mBuffer->Clear();
	}

	void ParticleShader::SetStrcutedBuffer(StructedBuffer* buffer)
	{
		mBuffer = buffer;

		renderer::ParticleSystemCB info = {};
		info.elementCount = mBuffer->GetStride();
		info.deltaTime = Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&info);
		cb->Bind(eShaderStage::CS);
	}

}
