//
//  main.cpp
//  khulagl
//
//  Created by Anirudh on 17/03/23.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.hpp"
#include "Shader.hpp"

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
    
    /* Initialize the glad library */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    std::vector<Vertex> vertices = {
        {-0.5f, 0.5f},
        { 0.5f, 0.5f},
        { 0.5f,-0.5f},
        {-0.5f,-0.5f},
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray vao;
    vao.layout.push<float>(2);
    vao.setVertices(vertices, indices);
    
    Shader shader("Resources/Shaders/Basic.shader");
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.setUniform4f("u_Color", 1.0, 1.0, 0.0, 1.0);
        
        vao.bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
