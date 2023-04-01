//
//  main.cpp
//  khulagl
//
//  Created by Anirudh on 17/03/23.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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
        // positions          // colors           // texture coords
        { 0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f}, // top right
        { 0.5f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f}, // bottom right
        {-0.5f,-0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f}, // bottom left
        {-0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f}  // top left
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    VertexArray vao;
    vao.layout.push<float>(3);
    vao.layout.push<float>(3);
    vao.layout.push<float>(2);
    vao.setVertices(vertices, indices);
    
    Shader shader("Resources/Shaders/Basic.shader");
    shader.setUniform1i("texture1", 0);
    shader.setUniform1i("texture2", 1);
    
    Texture texture1("Resources/Textures/container.jpg");
    Texture texture2("Resources/Textures/awesomeface.png");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        texture1.bind(0);
        texture2.bind(1);
        vao.bind();
        
        printf("%f\n", (float)glfwGetTime());
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        
        shader.setUniformMat4f("transform", trans);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
