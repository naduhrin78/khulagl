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

in vec2 v_Texture;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    color = mix(texture(texture1, v_Texture), texture(texture2, v_Texture), 0.2);
}
