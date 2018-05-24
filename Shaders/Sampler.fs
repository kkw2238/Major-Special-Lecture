#version 330

uniform sampler2D uTexSampler;
uniform int uIndex;
in vec2 vTexPos;

out vec4 FragColor;

const float pi = 3.141592;

void main()
{
	float shore = 4.0f;
	float repeat = 3.0f;
	float x = fract(fract(floor(vTexPos.y * shore) / repeat + fract(vTexPos.x * shore)));
	float y = fract(vTexPos.y * shore);


	vec2 uv = vec2(x, y);

	FragColor = texture(uTexSampler, uv);
	//FragColor = texture(uTexSampler, vTexPos).bgra;
}
