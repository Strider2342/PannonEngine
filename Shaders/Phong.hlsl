#define MAX_LIGHTS 8

#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

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

void VShader()
{

}