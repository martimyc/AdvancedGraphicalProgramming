#version 330

in Data
{
    vec3 color;
}FSIn;

out vec4 outColor;

void main(void)
{
    outColor = vec4(FSIn.color, 1.0);
}
