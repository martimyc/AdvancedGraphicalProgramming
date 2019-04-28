#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <future>

#include <QLabel>
#include <QTime>
#include <QLabel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QFrame>
#include <QTreeView>
#include <QFileSystemModel>
#include <QBoxLayout>
#include <QMessageBox>
#include <QImage>
#include <QFileDialog>

#include "ads/SectionWidget.h"
#include "ads/DropOverlay.h"

#include "dialogs/SectionContentListWidget.h"
#include "icontitlewidget.h"

#include "entitymanager.h"
#include "entity.h"
#include "openglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inspector(new QWidget),
    hierarchy(new EntityManager(this)),
    gl(new OpenGLWidget)
{
    ui->setupUi(this);

    // ADS - Create main container (ContainerWidget).
    _container = new ADS_NS::ContainerWidget();
#if QT_VERSION >= 0x050000
    QObject::connect(_container, &ADS_NS::ContainerWidget::activeTabChanged, this, &MainWindow::onActiveTabChanged);
    QObject::connect(_container, &ADS_NS::ContainerWidget::sectionContentVisibilityChanged, this, &MainWindow::onSectionContentVisibilityChanged);
#else
    QObject::connect(_container, SIGNAL(activeTabChanged(const SectionContent::RefPtr&, bool)), this, SLOT(onActiveTabChanged(const SectionContent::RefPtr&, bool)));
    QObject::connect(_container, SIGNAL(sectionContentVisibilityChanged(SectionContent::RefPtr,bool)), this, SLOT(onSectionContentVisibilityChanged(SectionContent::RefPtr,bool)));
#endif
    setCentralWidget(_container);

    // Setup actions.
    //QObject::connect(ui->actionContentList, SIGNAL(triggered()), this, SLOT(showSectionContentListDialog()));

    //Connect actions' triggered signals to slots
    connect(ui->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionSave_project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionSave_Screenshot, SIGNAL(triggered()), this, SLOT(saveScreenshot()));

    //Update inspector
    connect(hierarchy->GetTreeWidget(), SIGNAL(itemSelectionChanged()), this, SLOT(updateInspector()));

    //About
    connect(ui->actionAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->actionAboutOpenGL, SIGNAL(triggered()), this, SLOT(aboutOpenGL()));

    //Add widgets to containter
    //OpenGL
    _gl = ADS_NS::SectionContent::newSectionContent(QString("GL"), _container, new QLabel("Open GL"), gl);
    _container->addSectionContent(_gl, nullptr, ADS_NS::CenterDropArea);

    //Hierarchy
    _hierarchy = ADS_NS::SectionContent::newSectionContent(QString("Hierarchy"), _container, new QLabel("Hierarchy"), hierarchy);
    _container->addSectionContent(_hierarchy, nullptr, ADS_NS::LeftDropArea);

    //Inspector
    _inspector = ADS_NS::SectionContent::newSectionContent(QString("Inspector"), _container, new QLabel("Inspector"), inspector);
    rightSection = _container->addSectionContent(_inspector, rightSection, ADS_NS::RightDropArea);

    //Set Size
    resize(1080, 720);
}

MainWindow::~MainWindow()
{
    delete ui;

    //Delete widgets
    delete inspector;
    delete hierarchy;

    //Delete container
    delete _container;
}

void MainWindow::updateInspector()
{
    _container->removeSectionContent(_inspector);
    inspector = new QWidget;
    inspector->setLayout(hierarchy->GetFocused()->GenerateWidgets());
    _inspector = ADS_NS::SectionContent::newSectionContent(QString("Hi"), _container, new QLabel("Hi"), inspector);
    _container->addSectionContent(_inspector, nullptr, ADS_NS::RightDropArea);
}

void MainWindow::openProject() const
{
    std::cout << "Open project" << std::endl;
}

void MainWindow::saveProject() const
{
    std::cout << "Save project" << std::endl;
}

void MainWindow::quit()
{
    std::cout << "Quiting Application" << std::endl;
}

void MainWindow::saveScreenshot()
{
    QFileInfo fileInfo = QFileDialog::getSaveFileName(nullptr, "Save Screenshot", "screenshot", "PNG (*.PNG; *.PNS);;JPEG (*.JPG; *.JPEG; *.JPE)");

    if(fileInfo.fileName().isEmpty())
    {
        std::cout << "Save Screenshot: no file name" << std::endl;
        return;
    }
    else
    {
        async(std::launch::async, SaveScreenshot, fileInfo, gl->GetScreenshot());
    }
}

//About
void MainWindow::aboutOpenGL() const
{
    QMessageBox::about(nullptr, "About Open GL", gl->info.Print());
}

void MainWindow::aboutQt() const
{
    QMessageBox::aboutQt(nullptr, "About Qt");
}

///////////////////////////////////////////////////////////////////////
//Docking
///////////////////////////////////////////////////////////////////////

static int CONTENT_COUNT = 0;

static ADS_NS::SectionContent::RefPtr createLongTextLabelSC(ADS_NS::ContainerWidget* container)
{
    QWidget* w = new QWidget();
    QBoxLayout* bl = new QBoxLayout(QBoxLayout::TopToBottom);
    w->setLayout(bl);

    QLabel* l = new QLabel();
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    l->setText(QString("Lorem Ipsum ist ein einfacher Demo-Text für die Print- und Schriftindustrie. Lorem Ipsum ist in der Industrie bereits der Standard Demo-Text seit 1500, als ein unbekannter Schriftsteller eine Hand voll Wörter nahm und diese durcheinander warf um ein Musterbuch zu erstellen. Es hat nicht nur 5 Jahrhunderte überlebt, sondern auch in Spruch in die elektronische Schriftbearbeitung geschafft (bemerke, nahezu unverändert). Bekannt wurde es 1960, mit dem erscheinen von Letrase, welches Passagen von Lorem Ipsum enhielt, so wie Desktop Software wie Aldus PageMaker - ebenfalls mit Lorem Ipsum."));
    bl->addWidget(l);

    const int index = ++CONTENT_COUNT;
    ADS_NS::SectionContent::RefPtr sc = ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Label %1").arg(index)), w);
    sc->setTitle("Ein Label " + QString::number(index));
    return sc;
}

static ADS_NS::SectionContent::RefPtr createCalendarSC(ADS_NS::ContainerWidget* container)
{
    QCalendarWidget* w = new QCalendarWidget();

    const int index = ++CONTENT_COUNT;
    return ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Calendar %1").arg(index)), w);
}

static ADS_NS::SectionContent::RefPtr createFileSystemTreeSC(ADS_NS::ContainerWidget* container)
{
    QTreeView* w = new QTreeView();
    w->setFrameShape(QFrame::NoFrame);
    //	QFileSystemModel* m = new QFileSystemModel(w);
    //	m->setRootPath(QDir::currentPath());
    //	w->setModel(m);

    const int index = ++CONTENT_COUNT;
    return ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Filesystem %1").arg(index)), w);
}

static void storeDataHelper(const QString& fname, const QByteArray& ba)
{
    QFile f(fname + QString(".dat"));
    if (f.open(QFile::WriteOnly))
    {
        f.write(ba);
        f.close();
    }
}

static QByteArray loadDataHelper(const QString& fname)
{
    QFile f(fname + QString(".dat"));
    if (f.open(QFile::ReadOnly))
    {
        QByteArray ba = f.readAll();
        f.close();
        return ba;
    }
    return QByteArray();
}

///////////////////////////////////////////////////////////////////////

void MainWindow::showSectionContentListDialog()
{
    SectionContentListWidget::Values v;
    v.cw = _container;

    SectionContentListWidget w(this);
    w.setValues(v);
    w.exec();
}

void MainWindow::onActiveTabChanged(const ADS_NS::SectionContent::RefPtr& sc, bool active)
{
    Q_UNUSED(active);
    IconTitleWidget* itw = dynamic_cast<IconTitleWidget*>(sc->titleWidget());
    if (itw)
    {
        itw->polishUpdate();
    }
}

void MainWindow::onSectionContentVisibilityChanged(const ADS_NS::SectionContent::RefPtr& sc, bool visible)
{
    qDebug() << Q_FUNC_INFO << sc->uniqueName() << visible;
}

void MainWindow::onActionAddSectionContentTriggered()
{
    return;
}

void MainWindow::contextMenuEvent(QContextMenuEvent* e)
{
    Q_UNUSED(e);
    QMenu* m = _container->createContextMenu();
    m->exec(QCursor::pos());
    delete m;
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    Q_UNUSED(e);
    storeDataHelper("MainWindow", saveGeometry());
    storeDataHelper("ContainerWidget", _container->saveState());
}

// Threads
void SaveScreenshot(QFileInfo fileInfo, QImage image)
{
    if(image.save(fileInfo.filePath()) == false)
        std::cout << "Save Screenshot: could not save " << fileInfo.fileName().toStdString() << std::endl;
}
