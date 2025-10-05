#version 330 core

in vec2 vTexCoord;

uniform sampler2D uAtlasTexture;

out vec4 oFragColor;

void main()
{
    oFragColor = texture(uAtlasTexture, vTexCoord);
}