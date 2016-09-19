cbuffer ConstantBuffer
{
	float4x4 final;
	float4x4 rotation;
	float4 lightvector;
	float4 lightcolor;
	float4 ambientcolor;
}

Texture2D Texture : register(t0);
SamplerState ss : register(s0);

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut VShader(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
	VOut output;

	float intensity = 0.8;

	output.position = mul(final, position);
	output.color = ambientcolor;

	float4 normalized = normalize(mul(rotation, normal));
	float diffbrightness = saturate(dot(normalized, lightvector));
	output.color += (lightcolor * diffbrightness) * intensity;

	output.texcoord = texcoord;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return color;// *Texture.Sample(ss, texcoord);
}