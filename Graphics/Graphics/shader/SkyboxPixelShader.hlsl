TextureCube cubeTex;
SamplerState mainSampler : register(s0);

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 uv : TEXCOORD;
};

float4 main(PixelShaderInput INPUT) : SV_TARGET
{
    return cubeTex.Sample(mainSampler, INPUT.uv);
}