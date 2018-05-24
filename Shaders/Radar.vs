#version 410

uniform float u_Time;
uniform vec2 u_Startpos;
uniform vec2 u_Endpos;

in vec4 a_Position; //( -0.5, 0, 0, 0)
in vec4 a_Color;

out vec2 v_Value;
out vec4 v_Color;


void main()
{
	gl_Position = a_Position;
	v_Value = vec2(a_Position.x, a_Position.y);
}
