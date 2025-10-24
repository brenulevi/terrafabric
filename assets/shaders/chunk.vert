#version 460 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iTexCoord;

layout (std140, binding = 0) uniform Matrices
{
    mat4 uView;
    mat4 uProjection;
};

uniform mat4 uModel;

out vec2 vTexCoord;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
    vTexCoord = iTexCoord;
}