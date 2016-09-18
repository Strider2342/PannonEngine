cbuffer ConstantBuffer
{
	float4x4 final;
}

Texture2D Texture : register(t0);
SamplerState ss : register(s0);

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut VShader(float4 position : POSITION, float2 texcoord : TEXCOORD)
{
	VOut output;
    output.position = position;
	output.texcoord = texcoord;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return color * Texture.Sample(ss, texcoord);
}