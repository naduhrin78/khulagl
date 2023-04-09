//
//  Mesh.hpp
//  khulagl
//
//  Created by Anirudh on 09/04/23.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct MeshVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();

public:
        // mesh data
        std::vector<MeshVertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture>      textures;

        Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,
             std::vector<MeshTexture> textures);
        void Draw(Shader &shader);
};

#endif /* Mesh_hpp */
