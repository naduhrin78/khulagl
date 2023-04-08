//
//  IndexBuffer.cpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count):m_Count(count) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const { 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

