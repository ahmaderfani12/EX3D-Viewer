#ifndef MODEL_H
#define MODEL_H
#include "ShaderClass.h"
#include "Mesh.h"
#include<vector>;
#include "Texture.h";
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"shaderClass.h"

class Model
{
public:

    Model(std::string path, std::string texturePath, Shader& modelShader, Camera& mainCamera);
    Model();
    void Draw();
    void DeleteShader();

    std::string returnMeshDirection() { return meshDirection; }
private:
    
    Camera* camera;
    Shader* shader;

    std::vector<Mesh> meshes;
    std::string meshDirection;
    std::vector<Texture> textures;

    void SetTexture(std::string texturePath);
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};
#endif