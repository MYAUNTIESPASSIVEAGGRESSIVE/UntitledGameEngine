Texture2D texture0 : register(t2);
TextureCube skybox0 : register(t3);
sampler sampler0;

struct PIn
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float2 uv : TEXCOORD0;
    float3 uvw : TEXCOORD1;
};

cbuffer CbufferPS
{
    float transparency;
    float3 padding;
};

float4 main(PIn input) : SV_TARGET
{
    float4 sampled = texture0.Sample(sampler0, input.uv);
    float4 reflectedSampled = skybox0.Sample(sampler0, input.uvw);
    clip(sampled.a < 0.1f ? -1 : 1);
    float4 combined = ((input.colour * sampled) * (1.0 - transparency)) + (reflectedSampled * transparency); // hard coded mixes -> use constant buffers to be able to control this
    
    return saturate(combined);
}