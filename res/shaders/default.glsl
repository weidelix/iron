#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fTexCoords;

void main()
{
	gl_Position = projection * view * model * vPosition;
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
	vec4 tint;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_ao;
};

in vec2 fTexCoords;

uniform Material fMaterial;
uniform bool useAlbedo;
uniform bool useAO;

void main()
{
	// Set the albedo
	if (useAlbedo)
	{
		gl_FragColor = texture(fMaterial.texture_diffuse1, fTexCoords) * fMaterial.tint;
	}
	else
	{
		gl_FragColor = vec4(1.0f);
	}

	// Apply AO map
	if (useAO)
	{
		gl_FragColor = vec4(texture(fMaterial.texture_ao, fTexCoords).r) * gl_FragColor;
	}	
};