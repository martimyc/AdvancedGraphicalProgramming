#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <queue>

#include "import.h"
#include "glinfo.h"

class QOpenGLShaderProgram;
class QOpenGLDebugMessage;
class Resources;
class EntityManager;

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWidget(Resources& resources, EntityManager& entities, QWidget* parent = nullptr, bool zBuffer = true);
    ~OpenGLWidget() override;

    // Virtual Methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // Extras
    QImage GetScreenshot();

    // Import
    void Import();

    // Generate Standard Meshes
    void GenStandardMeshes();

private:
    // Import into GL
    void ImportAll();

public slots:
    void finalizeGL();
    void handleLoggedMessage(const QOpenGLDebugMessage& debugMessage);

public:
    //About info
    GLInfo info;

private:   
    // Depth Test
    bool enableZBuffer;
    bool enableZWrite;

    // Import
    std::queue<ImportMesh*> import;

    // Resources
    Resources& resources;

    // Entities
    EntityManager& entities;

};

#endif // OPENGLWIDGET_H
