#shader vertex
#version 330 core

uniform mat4 transform;

layout (location = 0) in vec3 vPos;
layout (location = 0) in vec3 vNormal;

out vec3 Normal;

void main()
{
    gl_Position = transform * vec4(vPos, 1.0);
    Normal = vNormal;
};

#shader fragment
#version 330 core

uniform vec4 fillColor;
out vec4 fragmentColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientStrength * lightColor;
    fragmentColor = fillColor * vec4(ambient, 1.0);
};
