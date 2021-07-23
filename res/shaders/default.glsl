#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fColor;
out vec2 fTexCoords;

void main()
{
	gl_Position = projection * view * model * vPosition;
	fColor = vec4(1.0, 1.0, 1.0, 1.0);
	fTexCoords = vTexCoords;
};

#shader fragment
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
	// oColor = texture(fMaterial.texture_diffuse1, fTexCoords);
};