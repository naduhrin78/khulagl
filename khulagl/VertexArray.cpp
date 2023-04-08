//
//  VertexArray.cpp
//  khulagl
//
//  Created by Anirudh on 21/03/23.
//

#include "VertexArray.hpp"

VertexArray::VertexArray() { 
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::setVertices(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    bind();

    m_VertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    layout.apply();
        
    unbind();
}



