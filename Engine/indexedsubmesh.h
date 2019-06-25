#ifndef INDEXEDSUBMESH_H
#define INDEXEDSUBMESH_H

#include "submesh.h"

class IndexedSubMesh : public SubMesh
{
public:
    IndexedSubMesh(VertexFormat* vertexFormat, size_t numVertices, size_t indiciesCount);
    ~IndexedSubMesh() override;

    void Initialize(OpenGLWidget& gl, const ImportMesh& inportInfo) override;
    void Draw(OpenGLWidget& gl) override;
    void Destroy() override;

private:
    size_t indiciesCount;

    QOpenGLBuffer ibo;
};

#endif // INDEXEDSUBMESH_H
