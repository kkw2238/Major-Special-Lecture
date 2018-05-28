#version 410

layout(location=0) out vec4 FragColor;

uniform sampler2D uTexSampler;
in float gray;
in vec2 texCoord;

void main()
{
	FragColor = texture(uTexSampler, texCoord);
	FragColor = FragColor * gray;
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
