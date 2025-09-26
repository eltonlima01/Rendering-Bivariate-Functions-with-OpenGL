#version 330 core

layout (location = 0) in vec2 vPos;

uniform mat4 uProjection, uView;

void main ()
{
    gl_Position = uProjection * uView * vec4 (vPos.x, 0.0f, vPos.y, 1.0f);
}