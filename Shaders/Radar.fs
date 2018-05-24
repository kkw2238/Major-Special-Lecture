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
	float weight = 0;

	for(int i = 0; i < 4; ++i) 
	{
		float distance = length(v_Value - u_Mid[i]);
		if(distance < 0.05f)
			weight += 0.8;
	}

	float distance1 = length(v_Value);
	float newTime = fract(u_Scale / 2) * 2;
	float finalColor = 0;

	if(distance1 > newTime - 0.02f && distance1 < newTime + 0.02f )
	{
		finalColor = weight + 0.2f;
	}
	//else 
	//	FragColor = vec4(1);
	//if(weight > 0)
	//	FragColor = vec4(weight);
	else
	{
		discard;
	}
	FragColor = vec4(finalColor);
}
