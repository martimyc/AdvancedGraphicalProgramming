#include "indexedsubmesh.h"

#include <iostream>

#include "openglwidget.h"

IndexedSubMesh::IndexedSubMesh(VertexFormat* vertexFormat, size_t numVertices, size_t indiciesCount): SubMesh(vertexFormat, numVertices), indiciesCount(indiciesCount)
{}

IndexedSubMesh::~IndexedSubMesh()
{}

void IndexedSubMesh::Initialize(OpenGLWidget& gl, const ImportMesh& inportInfo)
{
    // VAO
    vao.create();
    vao.bind();

    // VBO
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(inportInfo.data, int(inportInfo.dataSize));

    // IBO
    if(inportInfo.indicies != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(inportInfo.indicies, int(indiciesCount));
    }
    else
        std::cout << "IndexedSubMesh: can not initialize indicies" << std::endl;

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
    if(ibo.isCreated())
        ibo.release();
}

void IndexedSubMesh::Draw(OpenGLWidget& gl)
{
    vao.bind();
    gl.glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr);
    vao.release();
}

void IndexedSubMesh::Destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}
