#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include "transform.h"

static void initStyleSheet(QApplication& a)
{
    //Q_INIT_RESOURCE(ads); // If static linked.
    QFile f(":ads/stylesheets/default-windows.css");
    if (f.open(QFile::ReadOnly))
    {
        const QByteArray ba = f.readAll();
        f.close();
        a.setStyleSheet(QString(ba));
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    initStyleSheet(a);

    //Configuration of open GL surface format
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    format.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow mw;
    mw.show();
    return a.exec();
}

