cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;	// Umrechnung von Camera zu Screenspace
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;			// Umrechnung von World zu Camera
}

cbuffer PerObject : register(b2)
{
	matrix worldMatrix;			// Umrechnung von Object zu World
}

struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 uv : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float3 uv : TEXCOORD;
};

VertexShaderOutput main(VertexShaderInput INPUT )
{
    VertexShaderOutput OUT;
    matrix wvp = transpose(mul(mul(worldMatrix, viewMatrix), projectionMatrix));
	
    OUT.pos = mul(float4(INPUT.pos, 1.0f), wvp).xyww; //Set Pos to xyww instead of xyzw, so that z will always be 1 (furthest from camera)
    OUT.uv = INPUT.pos;

    return OUT;
}