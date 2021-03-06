#shader vertex
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = view * model * vec4(vPos, 1.0);
    FragPos = vec3(model * vec4(vPos, 1.0));
    Normal = normalize(vNormal);
    TexCoord = vTexCoord;
};

#shader fragment
#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform sampler2D object_texture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

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

    vec3 result = (ambient + diffuse + specular) * lightColor * texture(object_texture, TexCoord);
    fragmentColor = vec4(result, 1.0);
};
