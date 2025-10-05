#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTexCoord;

layout (std140, binding=0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

out vec2 vTexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(iPosition, 1.0);
    vTexCoord = iTexCoord;
}