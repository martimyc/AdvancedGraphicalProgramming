#include "openglwidget.h"

#include <iostream>

#include <QImage>
#include <QOpenGLDebugLogger>
#include <QVector3D>

#include "globals.h"
#include "resources.h"
#include "entitymanager.h"
#include "mesh.h"

#define SPHERE_H 32
#define SPHERE_V 16

OpenGLWidget::OpenGLWidget(Resources& resources, EntityManager& entities, QWidget* parent, bool zBuffer): QOpenGLWidget (parent), enableZBuffer(zBuffer), resources(resources), entities(entities)
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

    // Depth Test
    if (enableZBuffer)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        if(enableZWrite)
            glDepthMask(GL_TRUE);
        else
            glDepthMask(GL_FALSE);
    }
    else
        glDisable(GL_DEPTH_TEST);

    // Debug
    if(context()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
    {
        QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
        logger->initialize();

        connect(logger, SIGNAL(messageLogged(const QOpenGLDebugMessage &)), this, SLOT(handleLoggedMessage(const QOpenGLDebugMessage &)));
        logger->startLogging();
    }

    // Initialize info
    info.Initialize(*this);

    // Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    // Generate Standard Meshes
    GenStandardMeshes();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    //TODO Resize Textures
}

void OpenGLWidget::paintGL()
{
    // Import into GL using GL context
    ImportAll();

    // Paint scene
    // Background
    glClearDepth(1.0);
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw all Entities
    for(std::vector<Entity*>::const_iterator it = entities.entities.begin(); )
}

// Extras
QImage OpenGLWidget::GetScreenshot()
{
    makeCurrent();
    return grabFramebuffer();
}

void OpenGLWidget::GenStandardMeshes()
{
    // Sphere

    struct Vertex { QVector3D pos; QVector3D norm;};

    Vertex* sphere  = new Vertex[SPHERE_H*(SPHERE_V + 1)];
    for (int h = 0; h < SPHERE_H; ++h)
    {
        for(int v = 0; v < SPHERE_V + 1; ++v)
        {
            float nh = float(h) / SPHERE_H;
            float nv = float(v) / SPHERE_V - 0.5f;
            float angleh = 2 * PI * nh;
            float anglev = -PI * nv;
            int currentVertex = h * SPHERE_V + v;
            sphere[currentVertex].pos.setX(sinf(angleh) * cosf(anglev));
            sphere[currentVertex].pos.setY(-sinf(anglev));
            sphere[currentVertex].pos.setZ(cosf(angleh) * cosf(anglev));
            sphere[currentVertex].norm = sphere[currentVertex].pos;
        }
    }

    unsigned int* sphereIndices = new unsigned int[SPHERE_H * SPHERE_V * 6];
    for (int h = 0; h < SPHERE_H; ++h)
    {
        for(int v = 0; v < SPHERE_V; ++v)
        {
            int currentIndice = 6 * (h * SPHERE_V + v);
            sphereIndices[currentIndice + 0] = (h+0) * (SPHERE_V + 1) + v;
            sphereIndices[currentIndice + 1] = ((h+1) % SPHERE_H) * (SPHERE_V + 1) + v;
            sphereIndices[currentIndice + 2] = ((h+1) % SPHERE_H) * (SPHERE_V + 1) + v + 1;
            sphereIndices[currentIndice + 3] = (h+0) * (SPHERE_V + 1) + v;
            sphereIndices[currentIndice + 4] = ((h+1) % SPHERE_H) * (SPHERE_V + 1) + v + 1;
            sphereIndices[currentIndice + 5] = (h+0) * (SPHERE_V + 1) + v + 1;
        }
    }

    VertexFormat* sphereVertexFormat = new VertexFormat;
    sphereVertexFormat->AddVertexAtribute(0,3);
    sphereVertexFormat->AddVertexAtribute(sizeof(QVector3D), 3);

    size_t sphereNumVertices = SPHERE_H * SPHERE_V + 1;
    size_t sphereNumIndices = SPHERE_H * SPHERE_V * 6;
    ImportMesh* meshImport = new ImportMesh("Sphere", sphereNumVertices, (unsigned char*)sphere, sizeof(sphere), sphereIndices, sphereNumIndices, sphereVertexFormat);

    import.push(meshImport);
}

void OpenGLWidget::ImportAll()
{
    while(!import.empty())
    {
        ImportMesh* importing = import.front();
        Mesh* newMesh = resources.CreateMesh(importing->name);

        if(importing->indicies == nullptr)
            newMesh->AddSubMesh(*this, *importing);
        else
            newMesh->AddIndexedSubMesh(*this, *importing);

        delete importing;
        import.pop();
    }
}

// Slots
void OpenGLWidget::finalizeGL()
{
    std::cout << "OpenGLWidget: GL finalizing" << std::endl;
}

void OpenGLWidget::handleLoggedMessage(const QOpenGLDebugMessage& debugMessage)
{
    std::cout << "OpenGL Debug: " << debugMessage.severity() << ": " << debugMessage.message().toStdString() << std::endl;
}
