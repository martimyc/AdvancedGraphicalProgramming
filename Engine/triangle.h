#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class OpenGLWidget;

class Triangle
{
public:
    Triangle();

    void Initialize(OpenGLWidget& gl);
    void Draw(OpenGLWidget& gl);

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
};

#endif // TRIANGLE_H
