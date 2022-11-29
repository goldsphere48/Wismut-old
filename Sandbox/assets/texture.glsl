#type vertex
#version 450 core

layout(location = 0) in vec4 u_Position;
layout(location = 1) in vec2 u_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * u_Position;
	v_TexCoords = u_TexCoords;
}

#type fragment
#version 450 core

out vec4 FragColor;
in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoords);
}