#version 410

//in vec4 o_Color;
layout(location=0) out vec4 FragColor;

float pi = 3.141592;

in vec2 v_Value;
uniform vec4 u_Color;

uniform float u_Scale;
//uniform vec4 u_Color;

void main()
{
	// 원그리기
	//float dist = floor(distance(vec2(0.0f), v_Value) + 0.5f);
	//
	//vec4 color = vec4(dist, dist, dist, dist);
	//FragColor = color;

	//	clip(distance(vec2(0.0f), v_Value) - 0.5f);
	//if(distance(vec2(0.0f), v_Value) >= 0.5f)
	//	FragColor = vec4(1.0f);
	//else
	//	discard;
	//FragColor = vec4(1.0f);

	//float dist = distance(vec2(0.0f), v_Value);
	//
	//float color = sin(pi * dist * 10) * 1.5f;
	//color = fract(color);
	//
	//FragColor = vec4(color);

	FragColor = vec4(0);

	float x = cos(pi * u_Scale) * 0.25f;
	float y = sin(pi * u_Scale) * 0.25f;

	if(distance(vec2(x,y), v_Value) < 0.1f)
		FragColor = vec4(1.0f);
}
