#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class TransformWidget;
}

class Transform;

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(Transform& transform, QWidget *parent = nullptr);
    ~TransformWidget();

private slots:
    //Update UI to Transform
    //Translation
    void updateTranslationX() const;
    void updateTranslationY() const;
    void updateTranslationZ() const;

    //Rotation
    void updateRotation() const;

    //Scale
    void updateScaleX() const;
    void updateScaleY() const;
    void updateScaleZ() const;

private:
    Ui::TransformWidget *ui;
    Transform& transform;
};

#endif // TRANSFORMWIDGET_H
