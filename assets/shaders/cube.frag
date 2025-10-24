#version 460 core

in vec2 vTexCoord;

uniform sampler2D uTexture;

out vec4 oFragColor;

void main()
{
    oFragColor = texture(uTexture, vTexCoord);
}