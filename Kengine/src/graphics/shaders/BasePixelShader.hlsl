Texture2D texture0;
sampler sampler0;

struct PSinput
{
    float4 inPosition : SV_Position;
    float2 uv : TEXCOORD;
    float4 inColour : COLOR;
};

float4 main(PSinput input) : SV_TARGET
{
    float4 sampled = texture0.Sample(sampler0, input.uv);
    return input.inColour * sampled;
}