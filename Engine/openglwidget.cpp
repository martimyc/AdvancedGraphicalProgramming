#include "openglwidget.h"

#include <iostream>

#include <QImage>

#include "triangle.h"

OpenGLWidget::OpenGLWidget(QWidget* parent): QOpenGLWidget (parent)
{
    setMinimumSize(QSize(256, 256));
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Initialize info
    info.Initialize(*this);

    // Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    // Triangle
    tri = new Triangle;
    tri->Initialize(*this);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    //TODO Resize Textures
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    tri->Draw(*this);
}

// Extras
QImage OpenGLWidget::GetScreenshot()
{
    makeCurrent();
    return grabFramebuffer();
}

void OpenGLWidget::finalizeGL()
{
    std::cout << "OpenGLWidget: GL finalizing" << std::endl;

    delete tri;
}
