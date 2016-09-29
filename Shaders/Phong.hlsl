// constants
#define MAX_LIGHTS 8
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

Texture2D Texture		: register(t0);
SamplerState Sampler	: register(s0);

// light and material structs
struct Material
{
	float4  diffuse;
	float4  specular;
	float4  ambient;
	float4  emissive;
	
	float   specularPower;
	bool    useTexture;
	float2  padding;
};
struct Light
{
	float4 position;
	float4 direction;
	float4 color;

	float spotAngle;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	float intensity;
	int type;
	bool enabled;
	int padding;
};
struct LightingResult
{
	float4 diffuse;
	float4 specular;
};

// constant buffers
cbuffer PerObject			: register(b0)
{
	float4x4 WorldMatrix;
	float4x4 InverseTransposeWorldMatrix;
	float4x4 WorldViewProjectionMatrix;
}
cbuffer MaterialProperties	: register(b1)
{
	Material material;
}
cbuffer LightProperties		: register(b2)
{
	float4 eyePosition;
	float4 globalAmbient;
	Light lights[MAX_LIGHTS];
}

// shader structs
struct VSInput
{
	float3 position : POSITION;
	float3 normal	: NORMAL;
	float2 uv		: TEXCOORD;
};
struct VSOutput
{
	float4 positionWS	: TEXCOORD1;
	float3 normalWS		: TEXCOORD2;
	float2 uv			: TEXCOORD0;
	float4 position		: SV_POSITION;
};
struct PSInput
{
	float4 positionWS	: TEXCOORD1;
	float3 normalWS		: TEXCOORD2;
	float2 uv			: TEXCOORD0;
};

// functions
float4 DoDiffuse(Light light, float3 L, float3 N)
{
	float NdotL = max(0, dot(N, L));
	return light.color * NdotL;
}
float4 DoSpecular(Light light, float3 V, float3 L, float3 N)
{
	float3 R = normalize(reflect(-L, N));
	float RdotV = max(0, dot(R, V));

	return light.color * pow(RdotV, material.specularPower);
}
float DoAttenuation(Light light, float d)
{
	return 1.0 / (light.constantAttenuation + light.linearAttenuation * d + light.quadraticAttenuation * d * d);
}
float DoSpotCone(Light light, float3 L)
{
	float minCos = cos(light.spotAngle);
	float maxCos = (minCos + 1.0) / 2.0;
	float cosAngle = dot(light.direction.xyz, -L);

	return smoothstep(minCos, maxCos, cosAngle);
}

// light type functions
LightingResult DoPointLight(Light light, float3 V, float4 P, float3 N)
{
	LightingResult result;

	float3 L = (light.position - P).xyz;
	float distance = length(L);
	L = L / distance;

	float attenuation = DoAttenuation(light, distance);

	result.diffuse = DoDiffuse(light, L, N) * attenuation;
	result.specular = DoSpecular(light, V, L, N) * attenuation;

	return result;
}
LightingResult DoDirectionalLight(Light light, float3 V, float4 P, float3 N)
{
	LightingResult result;

	float3 L = -light.direction.xyz;

	result.diffuse = DoDiffuse(light, L, N);
	result.specular = DoSpecular(light, V, L, N);

	return result;
}
LightingResult DoSpotLight(Light light, float3 V, float4 P, float3 N)
{
	LightingResult result;

	float3 L = (light.position - P).xyz;
	float distance = length(L);
	L = L / distance;

	float attenuation = DoAttenuation(light, distance);
	float spotIntensity = DoSpotCone(light, L);

	result.diffuse = DoDiffuse(light, L, N) * attenuation * spotIntensity;
	result.specular = DoSpecular(light, V, L, N) * attenuation * spotIntensity;

	return result;
}

LightingResult ComputeLighting(float4 P, float3 N)
{
	float3 V = normalize(eyePosition - P).xyz;

	LightingResult totalResult = { { 0, 0, 0, 0 },{ 0, 0, 0, 0 } };

	[unroll]
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		LightingResult result = { { 0, 0, 0, 0 },{ 0, 0, 0, 0 } };

		if (!lights[i].enabled) continue;
		
		if (lights[i].type == DIRECTIONAL_LIGHT)
		{
			result = DoDirectionalLight(lights[i], V, P, N);
		}
		else if (lights[i].type == POINT_LIGHT)
		{
			result = DoPointLight(lights[i], V, P, N);
		}
		else if (lights[i].type == SPOT_LIGHT)
		{
			result = DoSpotLight(lights[i], V, P, N);
		}

		totalResult.diffuse += result.diffuse;
		totalResult.specular += result.specular;
	}

	totalResult.diffuse = saturate(totalResult.diffuse);
	totalResult.specular = saturate(totalResult.specular);

	return totalResult;
}

// shaders
VSOutput VShader(VSInput input)
{
	VSOutput output;

	output.position = mul(WorldViewProjectionMatrix, float4(input.position, 1.0));
	output.positionWS = mul(WorldMatrix, float4(input.position, 1.0));
	output.normalWS = mul((float3x3)InverseTransposeWorldMatrix, input.normal);
	output.uv = input.uv;

	return output;
}
float4 PShader(PSInput input) : SV_TARGET
{
	LightingResult lit = ComputeLighting(input.positionWS, normalize(input.normalWS));

	float4 emissive = material.emissive;
	float4 ambient = material.ambient * globalAmbient;
	float4 diffuse = material.diffuse * lit.diffuse;
	float4 specular = material.specular * lit.specular;

	float4 texColor = { 1, 1, 1, 1 };

	if (material.useTexture)
	{
		texColor = Texture.Sample(Sampler, input.uv);
	}

	float4 finalColor = (emissive + ambient + diffuse + specular) * texColor;

	return finalColor;
}