#include "glinfo.h"

#include "iostream"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

GLInfo::GLInfo()
{}

void GLInfo::Initialize(const QOpenGLContext* context)
{
    version = reinterpret_cast<char const *>(glGetString(GL_VERSION));
    renderer = reinterpret_cast<char const *>(glGetString(GL_RENDERER));
    vendor = reinterpret_cast<char const *>(glGetString(GL_VENDOR));
    glslVersion = reinterpret_cast<char const *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    //Extensions
    /*GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    for(int i = 0; i < numExtensions; i++)
    {
        const unsigned char* str = glGetStringi(GL_EXTENSIONS, GLuint(i))
        QString newExtension(reinterpret_cast<char const *>());
        extensions.push_back(newExtension);
    }*/

    //Surface Format info
    redBufferSize = context->format().redBufferSize();
    greenBufferSize = context->format().greenBufferSize();
    blueBufferSize = context->format().blueBufferSize();
    alphaBufferSize = context->format().alphaBufferSize();
    depthBufferSize = context->format().depthBufferSize();
}

void GLInfo::Print() const
{
    std::cout << "Open GL Version: " << version.toStdString() << std::endl;
    std::cout << "Open GL Renderer: " << renderer.toStdString() << std::endl;
    std::cout << "Open GL Vendor: " << vendor.toStdString() << std::endl;
    std::cout << "Open GLSL Version: " << glslVersion.toStdString() << std::endl;

    std::cout << std::endl;

    //Extensions
    std::cout << "Open GL Extensions: " << std::endl;
    for(std::vector<QString>::const_iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        std::cout << "- " << it->toStdString() << std::endl;
    }

    std::cout << std::endl;

    //Surface Format info
    std::cout << "Red Buffer Size: " << redBufferSize << std::endl;
    std::cout << "Green Buffer Size: " << greenBufferSize << std::endl;
    std::cout << "Blue Buffer Size: " << blueBufferSize << std::endl;
    std::cout << "Alpha Buffer Size: " << alphaBufferSize << std::endl;
    std::cout << "Depth Buffer Size: " << depthBufferSize << std::endl;
}
