#version 330 core

layout (location = 0) in vec2 vPos;

uniform mat4 uProjection, uView, uModel;

void main ()
{
    gl_Position = uProjection * uView * uModel * vec4 (vPos.x, 0.01f, vPos.y, 1.0f);
}