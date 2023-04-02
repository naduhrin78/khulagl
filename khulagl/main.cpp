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
#include "Camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{
    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;
    
    /* Compatibility hint with apple */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "KhulaGL", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    /* Initialize the glad library */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    std::vector<Vertex> vertices = {
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
        {0.5f, -0.5f, -0.5f,  1.0f, 0.0f },
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f },
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
        {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f },
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        {0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {0.5f, -0.5f, -0.5f,  1.0f, 1.0f },
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f },
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f },
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f }

    };
    
    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    VertexArray vao;
    vao.layout.push<float>(3);
    vao.layout.push<float>(2);
    vao.setVertices(vertices, indices);
    
    Shader shader("Resources/Shaders/Basic.shader");
    shader.setUniform1i("texture1", 0);
    shader.setUniform1i("texture2", 1);
    
    Texture texture1("Resources/Textures/container.jpg");
    Texture texture2("Resources/Textures/awesomeface.png");
    
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        texture1.bind(0);
        texture2.bind(1);
        
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setUniformMat4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.getViewMatrix();
        shader.setUniformMat4f("view", view);

        // render boxes
        vao.bind();
        
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setUniformMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}
