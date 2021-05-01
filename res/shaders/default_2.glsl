#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;

out vec4 fColor;

void main()
{
	gl_Position = vPosition;
	fColor = vec4(1.0, 0.6, 0.6, 1.0);
};

#shader fragment
#version 330 core 

in vec4 fColor;
out vec4 oColor;

void main()
{
	oColor = fColor;
};