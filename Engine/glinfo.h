#ifndef GLINFO_H
#define GLINFO_H

#include <vector>
#include <QString>

class QOpenGLContext;

class GLInfo
{
public:
    GLInfo();

    void Initialize(const QOpenGLContext* context); //Must call after initializing GL and with GL context active
    void Print() const;

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
