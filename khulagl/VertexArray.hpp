//
//  VertexArray.hpp
//  khulagl
//
//  Created by Anirudh on 21/03/23.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    
    void bind();
    void unbind();
    
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif /* VertexArray_hpp */
