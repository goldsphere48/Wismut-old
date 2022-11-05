#type vertex

#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 vColor;

void main()
{
	gl_Position = position;
	vColor = color;
}

#type fragment

#version 450 core

layout(location = 0) out vec4 color;
in vec4 vColor;

void main()
{
	color = vColor;
}