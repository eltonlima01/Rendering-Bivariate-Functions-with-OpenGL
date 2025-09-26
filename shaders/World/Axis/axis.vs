#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
out vec3 fColor;

uniform mat4 uProjection, uView;

void main ()
{
    gl_Position = uProjection * uView * vec4 (vPos, 1.0f);
    fColor = vColor;
}