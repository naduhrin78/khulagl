#Shader Vertex
#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 v_Texture;

void main()
{
    gl_Position = projection * view * model * position;
    v_Texture = texture;
}

#Shader Fragment
#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    color = vec4(lightColor * objectColor, 1.0);
}
