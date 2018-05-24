#version 410


in vec4 a_Position; //( -0.5, 0, 0, 0)

out vec2 v_Value;

void main()
{
	gl_Position = a_Position;
	gl_Position.w = 1.0f;

	v_Value = a_Position.xy;
}
