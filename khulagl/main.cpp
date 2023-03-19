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
    GLCall(unsigned int id = glCreateShader(type));
    const char* src =  source.c_str();
    
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    
    /* Error handling */
    int status;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
    
    if (status == GL_TRUE) {
        return id;
    }
    
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* message = (char*)alloca(sizeof(char) * length);
    
    GLCall(glGetShaderInfoLog(id, GL_INFO_LOG_LENGTH, &length, message));
    
    std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? " vertex " : " fragment ") << "shader" << std::endl;
    std::cout << message << std::endl;
    
    return 0;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    
    /* Error handling */
    GLCall(glValidateProgram(program));
    
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
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
    GLCall(glfwMakeContextCurrent(window));
    
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
    
    unsigned int vao;
    
    VertexBuffer vb(positions, 8 * sizeof(float));
    IndexBuffer ib(indices, 6);

    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
    
    ShaderSource source = ParseShader("Resources/Shaders/Basic.shader");
    
    std::string vertexShader = source.Vertex;
    
    std::string fragmentShader = source.Fragment;
    
    unsigned int program = CreateShader(vertexShader, fragmentShader);
    GLCall(glUseProgram(program));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        ib.bind();
        
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}
