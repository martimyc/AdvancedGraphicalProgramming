#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ads/API.h"
#include "ads/ContainerWidget.h"
#include "ads/SectionContent.h"

namespace Ui {
class MainWindow;
}

class EntityManager;
class Entity;
class OpenGLWidget;
class QImage;
class QFileInfo;
class Resources;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openProject() const;
    void saveProject() const;
    void quit();
    void saveScreenshot();

    //About
    void aboutOpenGL() const;
    void aboutQt() const;

private slots:
    void updateInspector();

    //Docking
public slots:
    void showSectionContentListDialog();

private slots:
#if QT_VERSION >= 0x050000
    void onActiveTabChanged(const ADS_NS::SectionContent::RefPtr& sc, bool active);
    void onSectionContentVisibilityChanged(const ADS_NS::SectionContent::RefPtr& sc, bool visible);
#else
    void onActiveTabChanged(const SectionContent::RefPtr& sc, bool active);
    void onSectionContentVisibilityChanged(const SectionContent::RefPtr& sc, bool visible);
#endif
    void onActionAddSectionContentTriggered();

protected:
    virtual void contextMenuEvent(QContextMenuEvent* e);
    virtual void closeEvent(QCloseEvent* e);
    //-----

private:
    Ui::MainWindow *ui;

    // The main container for dockings.
    ADS_NS::ContainerWidget* _container;

    // Widget references
    QWidget* inspector;
    EntityManager* hierarchy;
    Resources* resources;
    OpenGLWidget* gl;

    // Sections
    ADS_NS::SectionWidget* rightSection = nullptr;

    // Container references
    ADS_NS::SectionContent::RefPtr _inspector;
    ADS_NS::SectionContent::RefPtr _hierarchy;
    ADS_NS::SectionContent::RefPtr _gl;
    ADS_NS::SectionContent::RefPtr _resources;
};

// Threads
void SaveScreenshot(QFileInfo fileInfo, QImage image);

#endif // MAINWINDOW_H
