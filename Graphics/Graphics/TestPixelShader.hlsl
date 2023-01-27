

struct PixelInput
{
    float4 pos : SV_POSITION;
    float4 color : TEXCOORD1;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    //INPUT.pos.z = 1;
    
    return INPUT.color;
}