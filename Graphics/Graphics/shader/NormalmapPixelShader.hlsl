Texture2D mainTex : register(t0);
SamplerState mainSampler : register(s0);
Texture2D normalTex : register(t1);
SamplerState normalSampler : register(s1);

cbuffer Light : register(b0)
{
    float4 AmbientColor;
    float4 DiffuseColor;
    float4 SpecularColor;
    float3 LightDir;
    float filler;
    float3 CameraPos;
}

cbuffer PerObject : register(b1)
{
    matrix worldMatrix; // Umrechnung von Object zu World
}

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
    float4 posWorld : POSITION1;
    float2 uv : TEXCOORD;
};

float4 main(PixelShaderInput _in) : SV_TARGET
{
    float4 col = _in.color * mainTex.Sample(mainSampler, _in.uv);

    float3 ambient = col.xyz * AmbientColor.xyz * AmbientColor.a;
	
    float3 normal = normalTex.Sample(normalSampler, _in.uv);
    normal = normalize(normal * 2 - float3(1, 1, 1));
    normal = mul(transpose(worldMatrix), float4(normal, 0.0f)); // Lichtberechnung in World-space

    float3 diffuse = saturate(col.xyz
								* DiffuseColor.xyz
								* dot(normalize(-LightDir), normal)
								* DiffuseColor.a);
	
	// Hilfsvektor ist der durchschnitt aus Lichtrichtung und Punkt zu Kamera
	// dieser wird mit der normalen verglichen um bei übereinstimmung viel zu glänzen
    float3 halfVector = normalize(normalize(CameraPos - _in.posWorld.xyz) + normalize(-LightDir));

    float dotP = dot(halfVector, normal);
    dotP = pow(dotP, 100);

    float3 specular = saturate(SpecularColor.xyz * dotP * SpecularColor.w);


    return float4(saturate(ambient + diffuse + specular), _in.color.a);
}