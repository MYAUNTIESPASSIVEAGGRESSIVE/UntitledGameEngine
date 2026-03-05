#include "common.hlsli"

struct VSout
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD1;
    float4 colour : COLOR;
};

VSout main(VSinput input)
{
    VSout output;
    output.position = mul(WVP, float4(input.position, 1));
    output.uv = input.uv;
    
    output.colour = float4(1, 1, 1, 1);
    
    return output;
}