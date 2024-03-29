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
}