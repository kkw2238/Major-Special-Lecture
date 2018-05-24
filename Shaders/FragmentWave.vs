#version 410


in vec4 a_Position; //( -0.5, 0, 0, 0)
in vec4 a_Color;

out vec2 v_Value;
out vec4 v_Color;

void main()
{
	gl_Position = a_Position;
	v_Value = gl_Position.xy;
	v_Color = a_Color;

}
