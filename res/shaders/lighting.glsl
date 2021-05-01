#shader vertex
#version 330 core 

layout(location = 0) in vec4 vPosition;

out vec4 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vPosition;
	fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};


#shader fragment
#version 330 core 

in vec4 fColor;
out vec4 oColor;

void main()
{
	oColor = fColor;
};