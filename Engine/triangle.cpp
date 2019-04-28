#include "triangle.h"

#include <iostream>

#include "openglwidget.h"

Triangle::Triangle()
{

}

void Triangle::Initialize(OpenGLWidget& gl)
{    
    // Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag");
    program.link();
    program.bind();

    // VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), // Vertex 1
        QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), // Vertex 2
        QVector3D( 0.0f,    0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f) // Vertex 3
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof (QVector3D));

    // VAO: Captures state of VBOs
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    gl.glEnableVertexAttribArray(0);
    gl.glEnableVertexAttribArray(1);
    gl.glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    gl.glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    //Release
    vao.release();
    vbo.release();
    program.release();
}

void Triangle::Draw(OpenGLWidget& gl)
{
    if(program.bind())
    {
        vao.bind();
        gl.glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }
    else
        std::cout << "Triangle: program failed to bind" << std::endl;
}
