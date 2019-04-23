#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix3x3>
#include <QMatrix4x4>


class Transform: public Component
{
public:
    Transform(Entity* entity);

    //Getters
    //Translation
    float GetTranslationX() const;
    float GetTranslationY() const;
    float GetTranslationZ() const;
    const QVector3D& GetTranslation() const;

    //Rotation
    QVector3D GetEuler() const;
    const QQuaternion& GetRotation() const;
    QMatrix3x3 GetRotationMatrix() const;

    //Scale
    float GetScaleX() const;
    float GetScaleY() const;
    float GetScaleZ() const;
    const QVector3D& GetScale() const;

    //Setters
    //Translation
    void SetTranslationX(float newX);
    void SetTranslationY(float newY);
    void SetTranslationZ(float newZ);
    void SetTranslation(const QVector3D& newTranslation);

    //Rotation
    void SetRotation(const QVector3D& euler);
    void SetRotation(const QQuaternion& quaternion);
    void SetRotation(const QMatrix3x3& rotationMatrix);

    //Scale
    void SetScaleX(float newX);
    void SetScaleY(float newY);
    void SetScaleZ(float newZ);
    void SetScale(const QVector3D& newScale);

    //Operators
    Transform& operator = (const Transform& equalTo);
    Transform& operator = (const QMatrix4x4& equalTo);

    //QWidget
    virtual QWidget* GenerateWidget() override;

private:
    void UpdateMatrix();

    QMatrix4x4 transform;
    QVector3D translation;
    QQuaternion rotation;
    QVector3D scale;

};

#endif // TRANSFORM_H
