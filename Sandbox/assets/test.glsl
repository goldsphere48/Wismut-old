#type vertex

#version 450 core

layout(location = 0) in vec3 position;
layout(location = 0) in vec3 color;

out vec3 vColor;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0f);
	vColor = color;
}

#type fragment

#version 450 core

layout(location = 0) out vec4 color;
in vec3 vColor;

void main()
{
	color = vec4(vColor, 1);
}