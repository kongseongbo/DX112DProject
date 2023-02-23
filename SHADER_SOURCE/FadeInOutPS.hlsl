#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;

    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_TARGET
{
    if (onoff == 1)
       return float4(1.0f, 0.0f, 0.0f, (1.0f * fadeTime));
    //else if(onoff == 0)
    //   return float4(1.0f, 0.0f, 0.0f, (fadeTime / 1.0f));

    discard;
    return float4(0.0f, 0.0f, 0.0f, 0.0f);
}