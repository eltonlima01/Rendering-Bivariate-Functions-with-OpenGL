#version 330 core

layout (location = 0) in vec2 vPos;
out float height;

uniform mat4 uProjection, uView;
uniform float uTime;

void main ()
{
float e = 2.71828f;
float pi = 3.14159;

float x = vPos.x;
float z = vPos.y;
float y = sin (uTime) * ((x * z * ((x * x) - (z * z))) / ((x * x) + (z * z)));

height = y;
gl_Position = uProjection * uView * vec4 (x, y, z, 1.0f);
}