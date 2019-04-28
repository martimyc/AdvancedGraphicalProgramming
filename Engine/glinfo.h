#ifndef GLINFO_H
#define GLINFO_H

#include <vector>
#include <QString>

class OpenGLWidget;

class GLInfo
{
public:
    GLInfo();

    void Initialize(OpenGLWidget& gl); //Must call after initializing GL and with GL context active
    QString Print() const;

private:
    QString version;
    QString renderer;
    QString vendor;
    QString glslVersion;

    std::vector<QString> extensions;

    int redBufferSize;
    int greenBufferSize;
    int blueBufferSize;
    int alphaBufferSize;
    int depthBufferSize;
};

#endif // GLINFO_H
