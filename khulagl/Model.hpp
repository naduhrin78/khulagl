//
//  Model.hpp
//  khulagl
//
//  Created by Anirudh on 09/04/23.
//

#ifndef Model_hpp
#define Model_hpp

#include "Mesh.hpp"

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<MeshTexture> textures_loaded;


    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                          std::string typeName);
    
public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader &shader);
};

#endif /* Model_hpp */
