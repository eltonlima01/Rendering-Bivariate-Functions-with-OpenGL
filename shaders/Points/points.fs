#version 330 core

in float height;
out vec4 FragColor;

void main ()
{
    float h = clamp (height, 0.0f, 1.0f);

    vec3 color = mix (vec3 (0.0f, 0.0f, 1.0f), vec3 (1.0f, 0.0f, 0.0f), h);

    FragColor = vec4 (color, 1.0f);
}