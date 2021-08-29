#include "Model.h"


Model::Model(std::string path, std::string texturePath, Shader& modelShader, Camera& mainCamera)
{
    shader = &modelShader;
    camera = &mainCamera;

    SetTexture(texturePath);

    loadModel(path);
}

 Model::Model()
 {
 }

void Model::Draw() {
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(*shader, *camera);
}

void Model::SetTexture(std::string texturePath)
{
    Texture texturesX[]
    {
        Texture(texturePath.c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
    };
    textures = std::vector<Texture>(texturesX, texturesX + sizeof(texturesX) / sizeof(Texture));

}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    //ToDo:change it 
    /*Texture texturesX[]
    {
        Texture(textureDirectory.c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
    };*/

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture> textures;

    //textures = std::vector<Texture>(texturesX, texturesX + sizeof(texturesX) / sizeof(Texture));

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texUV = vec;
        }
        else
            vertex.texUV = glm::vec2(0.0f, 0.0f);

        vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);

        vertices.push_back(vertex);
    }
    // process indices
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    return Mesh(vertices, indices, textures);
}

void Model::DeleteShader()
{
    shader->Delete();
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::loadModel(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    meshDirection = path;
    processNode(scene->mRootNode, scene);
}
