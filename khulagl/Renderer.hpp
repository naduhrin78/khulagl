//
//  Renderer.hpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>

#define ASSERT(x) if ((!x)) __builtin_trap();

#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif /* Renderer_hpp */
