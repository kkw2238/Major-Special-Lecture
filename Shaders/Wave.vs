#version 410

uniform float u_Time;
uniform vec2 u_Startpos;
uniform vec2 u_Endpos;

in vec4 a_Position; //( -0.5, 0, 0, 0)

out vec2 v_Value;

void main()
{
	float pi = 3.141592;
	vec2 newPos = vec2(-10, -10);
	vec2 k = u_Endpos - u_Startpos ;

	float temp = 1.0f;

	mat2 rot = mat2(cos(pi/2), sin(pi/2), -sin(pi/2), cos(pi/2));
	vec2 verti = normalize(rot * k);

	if(u_Time> a_Position.x)
	{
		float newTime = u_Time - a_Position.x;
		newTime = fract(newTime / 2);
		temp = sin(newTime * pi * a_Position.y) * a_Position.z * 0.1f;
		newPos = u_Startpos + k * newTime;
		newPos.x += verti.x * temp / 1000.0f;
		newPos.y += verti.y * temp;
	}

	gl_Position = vec4 (
		newPos.x,
		newPos.y,
		0,
		1
	);
}
