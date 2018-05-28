#version 330

in vec3 Position;
in vec2 TexPos;
in vec4 Velocity;

uniform float uTime;

out vec2 vTexPos;
out float grayScale;
out vec4 vVelocity;

const vec3 g = vec3(0.0f, -0.3f, 0.0f);

void main()
{
	vec3 newPosition = vec3(0.0f);
	vec4 newVelocity = vec4(0.0f);
	float newTime = 0.0f;
	if( Velocity.w < uTime) {
		newTime = (uTime - Velocity.w);
		newTime = fract(newTime / 20) * 10;
		newVelocity = Velocity + Velocity * newTime;
		newPosition = Position + newTime * Velocity.xyz + 0.5 * (newTime * newTime) * g;
	}
	else 
		newPosition = vec3(-100.0f, -100.0f, -100.0f);

    gl_Position = vec4(newPosition, 1.0);

	grayScale = newTime;
	vTexPos = TexPos;
	vVelocity = newVelocity;
}