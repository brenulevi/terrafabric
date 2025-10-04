#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTexCoord;
layout (location = 2) in vec3 iNormal;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(iPosition, 1.0);
}