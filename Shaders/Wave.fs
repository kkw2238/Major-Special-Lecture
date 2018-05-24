#version 410

//in vec4 o_Color;
layout(location=0) out vec4 FragColor;

uniform sampler2D uTexSampler;

in vec2 v_Value;

uniform float u_Scale;
//uniform vec4 u_Color;

void main()
{
	
	FragColor = vec4(1.0f, 1.0f,1.0f,1);
}
