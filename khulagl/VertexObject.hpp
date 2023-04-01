//
//  VertexObject.hpp
//  khulagl
//
//  Created by Anirudh on 31/03/23.
//

#ifndef VertexObject_hpp
#define VertexObject_hpp

#include <stdio.h>
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexObject {
private:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
public:
    VertexBufferLayout vbl;
    
    VertexObject();
    ~VertexObject();
    
    void bind() const;
    void unbind() const;
};

#endif /* VertexObject_hpp */
