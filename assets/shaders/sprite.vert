#version 460 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iTexCoord;

layout (std140, binding=1) uniform Ortho
{
    mat4 ortho;
};

uniform mat4 model;

out vec2 vTexCoord;

void main()
{
    gl_Position = ortho * model * vec4(iPosition, 0.0, 1.0);
    vTexCoord = iTexCoord;
}