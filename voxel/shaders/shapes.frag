#version 330 core

out vec4 outColor;

uniform vec4 rainbowColor;

void main()
{
    outColor = rainbowColor; //vec4(1.0, 1.0, 1.0, 1.0);
}
