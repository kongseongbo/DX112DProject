cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer FadeInOut : register(b3)
{
    float4 fadePosition;
    float2 fadeResolution;
    float fadeTime;
    int onoff;
}

cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;

}

cbuffer ParticleSystem : register(b6)
{
    float4 worldPosition;
    float4 startColor;
    float4 startSize;

    uint maxParticles;
    uint simulationSpace;
    float radius;
    float startSpeed;

    float startLifeTime;
    float deltaTime;
    float elapsedTime; //누적시간
    int padding;
}

//cbuffer Noise : register(b7)
//{
//    float4 NoiseSize;
//}