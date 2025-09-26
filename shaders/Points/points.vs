#version 330 core

layout (location = 0) in vec2 vPos;
out float height;

uniform mat4 uProjection, uView, uModel;
uniform float uTime;

void main ()
{
    float e = 2.71828f,
    x = vPos.x,
    z = vPos.y,
    y = sin (uTime) * (x * z * ((x * x) - (z * z))) / ((x * x) + (z * z));
    //y = sin (uTime) * x * z * pow (e, -(z * z));
    //y = sin (uTime) * ((4 * x * x) + (z * z)) * pow (e, -((x* x) + (z * z)));
    //y = x * z;
    //y = sin (uTime) * (sin (x) + 2 * sin (z));
    //y = sin (uTime) * sqrt (x - (z * z));
    //y = sin (uTime) * sqrt (max (0.0f, 9.0f - ((x * x) + (z * z))));
    height = y;

    gl_Position = uProjection * uView * uModel * vec4 (x, y, z, 1.0f);
}