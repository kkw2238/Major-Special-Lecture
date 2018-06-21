#version 410

in vec3 a_Position; //( -0.5, 0, 0, 0)

uniform mat4 u_ProjView;

out vec2 texCoord; 
out float gray;

uniform float u_Time;
const float pi = 3.141592f;
const float g = 9.8f;


void main()
{
	vec4 newPos = u_ProjView * vec4(a_Position, 1.0f);
	float sinY = sin((newPos.x + 0.5f + u_Time) * pi * 2) / 2;

	gray = sinY;
	texCoord = vec2(a_Position.x + 0.5f - u_Time, 1.0f - (a_Position.y + 0.5f));
	gl_Position = vec4(newPos.x,
	newPos.y + 0.5 * sinY,
	newPos.z,
	1.0f);
}
