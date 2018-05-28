#version 410

in vec3 a_Position; //( -0.5, 0, 0, 0)

out vec2 texCoord; 
out float gray;

uniform float u_Time;
const float pi = 3.141592f;
const float g = 9.8f;


void main()
{
	float sinY = sin((a_Position.x + 0.5f + u_Time) * pi * 2) / 2;

	gray = sinY;
	texCoord = vec2(a_Position.x + 0.5f - u_Time, 1.0f - (a_Position.y + 0.5f));
	gl_Position = vec4(a_Position.x,
	a_Position.y + 0.5 * sinY,
	a_Position.z,
	1.0f);
}
