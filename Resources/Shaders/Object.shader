#Shader Vertex
#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 v_Texture;
out vec3 v_Normal;
out vec3 v_Fragment;

void main()
{
    gl_Position = projection * view * model * position;
    v_Texture = texture;
    v_Normal = normal;
    v_Fragment = vec3(model * position);
}

#Shader Fragment
#version 330 core

in vec3 v_Normal;
in vec3 v_Fragment;

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos-v_Fragment);
    float diffuseStrength = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - v_Fragment);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient+diffuse+specular) * objectColor;
    color = vec4(result, 1.0);
}
