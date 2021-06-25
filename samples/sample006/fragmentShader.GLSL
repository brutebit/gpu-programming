#version 410

out vec4 color;

void main()
{
    if (gl_FragCoord.x < 200)
        color = vec4(1.0, 0.0, 0.0, 1.0);
    else
        color = vec4(0.0, 0.0, 1.0, 1.0);
}
