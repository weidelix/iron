#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fColor;

void main()
{
	gl_Position = projection * view * model * vPosition;
	fColor = vec4(1.0, 1.0, 1.0, 1.0);
};

#shader fragment
#version 330 core

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

in vec4 fColor;
out vec4 oColor;

void main()
{
	oColor = fColor;
};