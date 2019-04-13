#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ads/API.h"
#include "ads/ContainerWidget.h"
#include "ads/SectionContent.h"

namespace Ui {
class MainWindow;
}

class Rendering;
class CustomPainter;
class EntityManager;
class Entity;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateInspector(Entity* focused);

public slots:
    void openProject();
    void saveProject();

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

private:
    Ui::MainWindow *ui;

    // The main container for dockings.
    ADS_NS::ContainerWidget* _container;

    //Widget references
    CustomPainter* customPainter;
    //Rendering* rendering;
    QWidget* inspector;
    EntityManager* hierarchy;

    //Sections
    ADS_NS::SectionWidget* right_section = nullptr;

    // Container references
    ADS_NS::SectionContent::RefPtr _customPainter;
    //ADS_NS::SectionContent::RefPtr _rendering;
    ADS_NS::SectionContent::RefPtr _inspector;
    ADS_NS::SectionContent::RefPtr _hierarchy;
};

#endif // MAINWINDOW_H
