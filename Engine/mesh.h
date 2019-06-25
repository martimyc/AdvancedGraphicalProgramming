#ifndef MESH_H
#define MESH_H

#include <vector>

#include "resource.h"

class SubMesh;
class aiNode;
class aiScene;
class OpenGLWidget;
class ImportMesh;

class Mesh: public Resource
{
public:
    Mesh();
    ~Mesh() override;

    // Basic Functions
    void Update() override;
    void Destroy() override;

    // Getters
    Mesh* AsMesh() override;

    // SubMesh
    void AddSubMesh(OpenGLWidget& gl, ImportMesh& import);
    void AddIndexedSubMesh(OpenGLWidget& gl, ImportMesh& import);
    void DeleteSubMesh();

private:
    std::vector<const SubMesh*> submeshes;

    // Assimp
    void procesNode(aiNode* node, const aiScene* scene);
    SubMesh* processNode(aiNode* node, const aiScene* scene);
};

#endif // MESH_H
