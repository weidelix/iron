#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
};

in vec2 fTexCoords;
in vec4 fColor;

uniform Material fMaterial;

out vec4 oColor;

void main()
{
	oColor = mix(fColor, texture(fMaterial.texture_diffuse1, fTexCoords), 1.0);
}