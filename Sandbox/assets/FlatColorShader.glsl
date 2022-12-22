#type vertex
#version 450

layout(location = 0) in vec3 v_Position;

uniform mat4 u_MVP;
uniform vec4 u_Color;
uniform int i = 1;

out vec4 v_Color;

void main()
{
    v_Color = u_Color;
    gl_Position = u_MVP * vec4(v_Position, 1.0f) * i;
}

#type fragment
#version 450

in vec4 v_Color;

uniform int i = 1;

out vec4 Color;

void main()
{
    Color = v_Color * i;
}