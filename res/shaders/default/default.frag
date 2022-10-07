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
uniform bool useSpecular;
uniform vec3 viewPos;

void main()
{
	vec4 defaultColor = vec4(1.0f);

	vec3 lightPos = vec3(0.0, 0.0, 5.0);
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 0.5);

	// Ambient
	float ambientStrength = 0.1;

	// Diffuse 
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	
	// Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
	vec4 ambient = ambientStrength * lightColor * texture(material.texture_diffuse1, fTexCoords);
	vec4 diffuse =  diff * texture(material.texture_diffuse1, fTexCoords).rgba * material.tint;
	vec4 specular = specularStrength * spec * vec4(texture(material.texture_specular1, fTexCoords).r);  
	
	vec4 result = ambient + diffuse + specular;

	gl_FragColor = vec4(texture(material.texture_ao, fTexCoords).r) * result;	
}