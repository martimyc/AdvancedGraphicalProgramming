#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "vertexformat.h"
#include "import.h"

class OpenGLWidget;

class SubMesh
{
public:
    SubMesh(VertexFormat* vertexFormat, size_t numVertices);
    virtual ~SubMesh();

    virtual void Initialize(OpenGLWidget& gl, const ImportMesh& inportInfo);
    virtual void Draw(OpenGLWidget& gl);
    virtual void Destroy();

protected:
    size_t numVertices;

    VertexFormat* vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
};

#endif // SUBMESH_H
