#version 330

in vec2 vTexPos;
in float grayScale;
in vec4 vVelocity;

out vec4 FragColor;


uniform sampler2D uTexture;

void main()
{
	vec4 color = texture(uTexture, vTexPos).brga;

	color.r = color.r * (-vVelocity.x);
	color.g = color.g * (-vVelocity.y);
	color.b = color.b * (-vVelocity.z);
	color.a = color.a * (3.0f - grayScale);
    FragColor = color;
}