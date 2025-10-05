#version 460 core

in vec2 vTexCoord;

uniform sampler2D uSprite;

out vec4 oFragColor;

void main()
{
    oFragColor = texture(uSprite, vTexCoord);
}