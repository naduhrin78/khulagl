//
//  VertexArray.cpp
//  khulagl
//
//  Created by Anirudh on 21/03/23.
//

#include "VertexArray.hpp"

VertexArray::VertexArray() { 
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::bind() {
    glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    
    std::vector<VertexBufferElement> elements = layout.getElements();
    
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (const void*) offset);
        
        offset += elements[i].size();
    }
}




