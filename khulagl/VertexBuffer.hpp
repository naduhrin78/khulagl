//
//  VertexBuffer.hpp
//  khulagl
//
//  Created by Anirudh on 19/03/23.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

class VertexBuffer {
private:
    unsigned int id;
public:
    VertexBuffer(const void* data, unsigned int count);
    ~VertexBuffer();
    
    void bind() const;
    void unbind() const;
};

#endif /* VertexBuffer_hpp */
