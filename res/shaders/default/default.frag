#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	vec4 tint;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_ao;
};

in vec2 fTexCoords;

uniform Material fMaterial;

out vec4 oColor;

void main()
{
	// Set the albedo
	oColor = texture(fMaterial.texture_diffuse1, fTexCoords) * fMaterial.tint;

	// Apply AO map
	oColor = vec4(texture(fMaterial.texture_ao, fTexCoords).r) * oColor;
}