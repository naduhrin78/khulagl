//
//  main.cpp
//  khulagl
//
//  Created by Anirudh on 17/03/23.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};

static ShaderSource ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);
    std::stringstream ss[2];
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    ShaderType mode = ShaderType::NONE;
    std::string line;
    
    while (getline(stream, line)) {
        if (line.find("#Shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                mode = ShaderType::VERTEX;
            }
            else if (line.find("Fragment") != std::string::npos) {
                mode = ShaderType::FRAGMENT;
            }
            
            continue;
        }
        
        ss[(int)mode] << line << '\n';
    }
    
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src =  source.c_str();
    
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    /* Error handling */
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    
    if (status == GL_TRUE) {
        return id;
    }
    
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(sizeof(char) * length);
    
    glGetShaderInfoLog(id, GL_INFO_LOG_LENGTH, &length, message);
    
    std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? " vertex " : " fragment ") << "shader" << std::endl;
    std::cout << message << std::endl;
    
    return 0;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    /* Error handling */
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;
    
    /* Compatibility hint with apple */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Initialize the glew library */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    
    float positions[8] = {
        -0.5f, 0.5f,
         0.5f, 0.5f,
         0.5f,-0.5f,
        -0.5f,-0.5f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray vao;
    
    VertexBuffer vb(positions, 8 * sizeof(float));
    IndexBuffer ib(indices, 6);
    
    VertexBufferLayout layout;
    layout.push<float>(2);
    
    vao.addBuffer(vb, layout);
    
    ShaderSource source = ParseShader("Resources/Shaders/Basic.shader");
    
    std::string vertexShader = source.Vertex;
    
    std::string fragmentShader = source.Fragment;
    
    unsigned int program = CreateShader(vertexShader, fragmentShader);
    glUseProgram(program);
    
    int location = glGetUniformLocation(program, "u_Color");
    glUniform4f(location, 1.0, 1.0, 0.0, 1.0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}
