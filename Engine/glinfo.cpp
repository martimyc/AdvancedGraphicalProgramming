#include "glinfo.h"

#include <sstream>

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

QString GLInfo::Print() const
{
    std::stringstream ss;

    ss << "Open GL Version: " << version.toStdString() << std::endl;
    ss << "Open GL Renderer: " << renderer.toStdString() << std::endl;
    ss << "Open GL Vendor: " << vendor.toStdString() << std::endl;
    ss << "Open GLSL Version: " << glslVersion.toStdString() << std::endl;

    ss << std::endl;

    //Surface Format info
    ss << "Surface Format Information:" << std::endl;
    ss << "Red Buffer Size: " << redBufferSize << std::endl;
    ss << "Green Buffer Size: " << greenBufferSize << std::endl;
    ss << "Blue Buffer Size: " << blueBufferSize << std::endl;
    ss << "Alpha Buffer Size: " << alphaBufferSize << std::endl;
    ss << "Depth Buffer Size: " << depthBufferSize << std::endl;

    ss << std::endl;

    //Extensions
    ss << "Open GL Extensions: " << std::endl;
    for(std::vector<QString>::const_iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        ss << it->toStdString() << ", ";
    }

    return QString(ss.str().c_str());
}
