#pragma once

struct Camera
{
    float fov = 90.0f;
    float aspectRatio = 4.0f / 3.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;
};