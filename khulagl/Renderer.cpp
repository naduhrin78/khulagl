//
//  Renderer.cpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#include "Renderer.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
        " " << file << ":" << line << std::endl;
        
        return false;
    }
    
    return true;
}
