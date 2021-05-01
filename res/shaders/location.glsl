#shader vertex
#version 330 core 

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vText_Coord;
layout(location = 3) in vec3 vNormal;

out vec4 fColor;
out vec2 fText_Coord;
out vec3 fFragPos;
out vec3 fNormal;

//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	gl_Position = projection * view * model * vPosition;
	fText_Coord = vText_Coord;
	fColor = vColor;
	fFragPos = vec3(model * vPosition);
	fNormal = vNormal;
};


#shader fragment
#version 330 core 

in vec2 fText_Coord;
in vec4 fColor;
in vec3 fNormal;
in vec3 fFragPos;

uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float specularStrength;
uniform int shineIntensity;
uniform float ambientStrength;
uniform float brightness;

out vec4 oColor;

void main()
{
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fFragPos); 
	vec3 viewDir = normalize(cameraPos - fFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shineIntensity);
	vec3 specular = specularStrength * spec * lightColor;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = ((ambient + diffuse + specular) * fColor.xyz) * brightness;
	oColor = vec4(result, 1.0);
};