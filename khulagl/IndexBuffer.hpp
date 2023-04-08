//
//  IndexBuffer.hpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp
#include "glad/glad.h"

class IndexBuffer {
private:
    unsigned int id;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* indices, unsigned int size);
    ~IndexBuffer();
    
    void bind() const;
    void unbind() const;
};

#endif /* IndexBuffer_hpp */
