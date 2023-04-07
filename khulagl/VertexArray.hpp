//
//  VertexArray.hpp
//  khulagl
//
//  Created by Anirudh on 21/03/23.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

class VertexArray {
private:
    unsigned int m_RendererID;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    VertexBufferLayout m_VertexBufferLayout;
public:
    VertexBufferLayout layout;
    
    VertexArray();
    ~VertexArray();
    
    void bind();
    void unbind();
        
    void setVertices(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};

#endif /* VertexArray_hpp */
