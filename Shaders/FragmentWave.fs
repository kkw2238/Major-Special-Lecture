#version 410

//in vec4 o_Color;
layout(location=0) out vec4 FragColor;

in vec2 v_Value;
in vec4 v_Color;

const float pi = 3.141592;

uniform float u_Scale;
uniform vec2 u_Mid[4];
//uniform vec4 u_Color;

void main()
{
	vec2 pos	= v_Value;
	FragColor = vec4(0);
	for(int i = 0; i <4 ; ++i)
	{
		vec2 pos	= v_Value;
		vec2 center = vec2(u_Mid[i]);
		float dist = distance(pos, center) * 2 * pi;

		float color = sin(dist * 5 - u_Scale) * clamp(1 - dist/( 2 * pi ), 0, 1);
		 FragColor += vec4(color, color, color, 1 - dist);
	}
}
