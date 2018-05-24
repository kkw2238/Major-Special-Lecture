#version 330

in vec3 Position;
in vec2 TexPos;

out vec2 vTexPos;

void main()
{
    gl_Position = vec4(Position, 1.0);
    vTexPos = TexPos;
}
