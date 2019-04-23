#include "glinfo.h"

#include "iostream"

#include "openglwidget.h"

GLInfo::GLInfo()
{}

void GLInfo::Initialize(OpenGLWidget& gl)
{
    version = reinterpret_cast<char const *>(gl.glGetString(GL_VERSION));
    renderer = reinterpret_cast<char const *>(gl.glGetString(GL_RENDERER));
    vendor = reinterpret_cast<char const *>(gl.glGetString(GL_VENDOR));
    glslVersion = reinterpret_cast<char const *>(gl.glGetString(GL_SHADING_LANGUAGE_VERSION));

    //Extensions
    GLint numExtensions;
    gl.glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    for(int i = 0; i < numExtensions; i++)
    {
        extensions.push_back(reinterpret_cast<char const *>(gl.glGetStringi(GL_EXTENSIONS, GLuint(i))));
    }

    //Surface Format info
    redBufferSize = gl.context()->format().redBufferSize();
    greenBufferSize = gl.context()->format().greenBufferSize();
    blueBufferSize = gl.context()->format().blueBufferSize();
    alphaBufferSize = gl.context()->format().alphaBufferSize();
    depthBufferSize = gl.context()->format().depthBufferSize();
}

void GLInfo::Print() const
{
    QString text;

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
