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
    v_Normal = mat3(transpose(inverse(model))) * normal;
    v_Fragment = vec3(model * position);
}

#Shader Fragment
#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_Texture;
in vec3 v_Normal;
in vec3 v_Fragment;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

vec3 calculate_emission()
{
    vec3 show = step(vec3(1.0), vec3(1.0) - texture(material.specular, v_Texture).rgb);
    return texture(material.emission, v_Texture).rgb * show;
}

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, v_Texture).rgb;
    
    // diffuse
    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(light.position-v_Fragment);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_Texture).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - v_Fragment);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec *  texture(material.specular, v_Texture).rgb;
    
    // emission
    vec3 emission = calculate_emission();
    
    vec3 result = emission+ambient+diffuse+specular;
    color = vec4(result, 1.0);
}
