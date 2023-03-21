//
//  IndexBuffer.cpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count):m_Count(count) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const { 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

