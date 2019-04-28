#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "glinfo.h"

class QOpenGLShaderProgram;
class Triangle;

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget() override;

    // Virtual Methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // Extras
    QImage GetScreenshot();

public slots:
    void finalizeGL();

public:
    //About info
    GLInfo info;

    Triangle* tri;
};

#endif // OPENGLWIDGET_H
