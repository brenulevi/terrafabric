#version 460 core

in vec2 vTexCoord;

out vec4 oFragColor;

void main()
{
    oFragColor = vec4(vTexCoord, 0.0, 1.0);
}