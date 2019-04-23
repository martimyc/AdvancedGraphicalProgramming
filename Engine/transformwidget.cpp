#include "transformwidget.h"
#include "ui_transformwidget.h"

#include "transform.h"

TransformWidget::TransformWidget(Transform& transform, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget),
    transform(transform)
{
    ui->setupUi(this);

    //Set up UI values
    //Translation
    ui->translation_x->setValue(transform.GetTranslationX());
    ui->translation_y->setValue(transform.GetTranslationY());
    ui->translation_z->setValue(transform.GetTranslationZ());

    //Translation
    QVector3D euler = transform.GetEuler();
    ui->rotation_x->setValue(euler.x());
    ui->rotation_y->setValue(euler.y());
    ui->rotation_z->setValue(euler.z());

    //Translation
    ui->scale_x->setValue(transform.GetScaleX());
    ui->scale_y->setValue(transform.GetScaleY());
    ui->scale_z->setValue(transform.GetScaleZ());

    //Connect
    //Translation
    connect(ui->translation_x, SIGNAL(valueChanged()), this, SLOT(updateTranslationX()));
    connect(ui->translation_y, SIGNAL(valueChanged()), this, SLOT(updateTranslationY()));
    connect(ui->translation_z, SIGNAL(valueChanged()), this, SLOT(updateTranslationZ()));

    //Rotation
    connect(ui->rotation_x, SIGNAL(valueChanged()), this, SLOT(updateRotation()));
    connect(ui->rotation_y, SIGNAL(valueChanged()), this, SLOT(updateRotation()));
    connect(ui->rotation_z, SIGNAL(valueChanged()), this, SLOT(updateRotation()));

    //Scale
    connect(ui->scale_x, SIGNAL(valueChanged()), this, SLOT(updateScaleX()));
    connect(ui->scale_y, SIGNAL(valueChanged()), this, SLOT(updateScaleY()));
    connect(ui->scale_z, SIGNAL(valueChanged()), this, SLOT(updateScaleZ()));
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

//Translation
void TransformWidget::updateTranslationX() const
{
    transform.SetTranslationX(ui->translation_x->value());
}

void TransformWidget::updateTranslationY() const
{
    transform.SetTranslationY(ui->translation_y->value());
}

void TransformWidget::updateTranslationZ() const
{
    transform.SetTranslationZ(ui->translation_z->value());
}

//Rotation
void TransformWidget::updateRotation() const
{
    QVector3D euler(ui->rotation_x->value(), ui->rotation_y->value(), ui->rotation_z->value());
    transform.SetRotation(euler);
}

//Scale
void TransformWidget::updateScaleX() const
{
    transform.SetScaleX(ui->scale_x->value());
}

void TransformWidget::updateScaleY() const
{
    transform.SetScaleY(ui->scale_y->value());
}

void TransformWidget::updateScaleZ() const
{
    transform.SetScaleZ(ui->scale_z->value());
}
