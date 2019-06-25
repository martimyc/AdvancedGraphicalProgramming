#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include <QWidget>

class Entity;
class QTreeWidget;

namespace Ui {
class EntityManager;
}

class EntityManager : public QWidget
{
    Q_OBJECT

public:
    explicit EntityManager(QWidget *parent = nullptr);
    ~EntityManager();

    // Create
    Entity* CreateEntity(Entity* parent = nullptr, QString name = NULL);

    // Delete
    void DeleteEntity(Entity *del);

    // Getters
    Entity* GetFocused() const;
    const QTreeWidget* GetTreeWidget() const;

    // Draw
    void DrawEntities() const;

public slots:
    void createEntityButton();
    void deleteEntityButton();

private:
    Ui::EntityManager *ui;
    std::vector<Entity*> entities;
    Entity* root;
};

#endif // ENTITYMANAGER_H
