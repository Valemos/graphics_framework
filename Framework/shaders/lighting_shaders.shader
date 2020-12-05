#shader vertex
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 view;
uniform mat4 model;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = view * model * vec4(vPos, 1.0);
    FragPos = vec3(model * vec4(vPos, 1.0));
    Normal = normalize(vNormal);
};

#shader fragment
#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform vec3 lightColor;
uniform vec4 fillColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 fragmentColor;

void main()
{
    float ambient = 0.1;
    float specularStrength = 0.5;

    // calculate diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuse = max(dot(lightDir, Normal), 0.0);

    // calculate specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * lightColor * fillColor.xyz;
    fragmentColor = vec4(result, 1.0);
};
