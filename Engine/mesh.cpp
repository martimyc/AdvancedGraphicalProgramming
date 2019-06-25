#include "mesh.h"

#include "import.h"
#include "openglwidget.h"
#include "submesh.h"
#include "indexedsubmesh.h"

Mesh::Mesh(): Resource (MESH)
{}

Mesh::~Mesh()
{}

// Basic Functions
void Mesh::Update()
{

}

void Mesh::Destroy()
{

}

// Getters
Mesh* Mesh::AsMesh()
{
    return this;
}

// SubMesh
void Mesh::AddSubMesh(OpenGLWidget& gl, ImportMesh& import)
{
    SubMesh newSubMesh(import.vertexFormat, import.num_vertices);
    newSubMesh.Initialize(gl, import);
}

void Mesh::AddIndexedSubMesh(OpenGLWidget& gl, ImportMesh& import)
{
    IndexedSubMesh newSubMesh(import.vertexFormat, import.num_vertices, import.indiciesCount);
    newSubMesh.Initialize(gl, import);
}

void Mesh::DeleteSubMesh()
{

}

// Assimp
void Mesh::procesNode(aiNode* node, const aiScene* scene)
{

}

SubMesh* Mesh::processNode(aiNode* node, const aiScene* scene)
{
return nullptr;
}
