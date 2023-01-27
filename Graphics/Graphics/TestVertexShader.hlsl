cbuffer MatrixBuffer : register(b0)
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
};

struct VertexInput
{
    float4 pos : POSITION;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : TEXCOORD1;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUT;
    
    OUT.pos = mul(INPUT.pos, worldViewProjectionMatrix);
    OUT.color = OUT.pos;
    
    return OUT;
}