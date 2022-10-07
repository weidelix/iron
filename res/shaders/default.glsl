#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fTexCoords;
out vec3 fNormal;
out vec3 fFragPos;

void main()
{
	gl_Position = projection * view * model * vPosition;
	fTexCoords = vTexCoords;
	fNormal = mat3(transpose(inverse(model))) * vNormal;
	fFragPos = vec3(model * vPosition);
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
	sampler2D texture_normal;
	sampler2D texture_ao;
};

in vec2 fTexCoords;
in vec3 fNormal;
in vec3 fFragPos;

uniform Material material;
uniform bool useAlbedo;
uniform bool useAO;
uniform bool useNormal;
uniform vec3 viewPos;

void main()
{
	gl_FragColor = vec4(1.0f);
	
	if (useAlbedo)
	{
		gl_FragColor = texture(material.texture_diffuse1, fTexCoords) * material.tint;
	}

	vec3 lightPos = vec3(0.0, 0.0, 5.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse 
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff * texture(material.texture_diffuse1, fTexCoords).rgb);
	
	gl_FragColor = vec4(ambient + diffuse, 1.0);
	
	if (useAO)
	{
		gl_FragColor = vec4(texture(material.texture_ao, fTexCoords).r) * gl_FragColor;
	}
};