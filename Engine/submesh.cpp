#include "submesh.h"

#include "openglwidget.h"

SubMesh::SubMesh(VertexFormat* vertexFormat, size_t numVertices): numVertices(numVertices), vertexFormat(vertexFormat)
{}

SubMesh::~SubMesh()
{
    // Delete ptr created on Import
    if(vertexFormat != nullptr) delete vertexFormat;
}

void SubMesh::Initialize(OpenGLWidget& gl, const ImportMesh& inportInfo)
{
    // VAO
    vao.create();
    vao.bind();

    // VBO
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(inportInfo.data, int(inportInfo.dataSize));

    uint num_atributtes = vertexFormat->attributes.size();

    for(uint i = 0; i < num_atributtes; i++)
    {
        VertexAttribute& vertexAttribute = vertexFormat->attributes[i];

        if(vertexAttribute.enabled)
        {
            gl.glEnableVertexAttribArray(GLuint(i));
            gl.glVertexAttribPointer(GLuint(i), vertexAttribute.ncomp, GL_FLOAT, GL_FALSE, vertexFormat->size, (void*) vertexAttribute.offset);
        }
    }

    // Release
    vao.release();
    vbo.release();
}

void SubMesh::Draw(OpenGLWidget& gl)
{
    vao.bind();
    gl.glDrawArrays(GL_TRIANGLES, 0, numVertices);
    vao.release();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(vao.isCreated()) vao.destroy();
}
