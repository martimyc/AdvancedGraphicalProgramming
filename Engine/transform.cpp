#include "transform.h"

#include "transformwidget.h"

Transform::Transform(Entity* entity):Component(entity), scale(1.0f, 1.0f, 1.0f)
{}

//Getters
//Translation
float Transform::GetTranslationX() const
{
    return translation.x();
}

float Transform::GetTranslationY() const
{
    return translation.y();
}

float Transform::GetTranslationZ() const
{
    return translation.z();
}

const QVector3D& Transform::GetTranslation() const
{
    return translation;
}

//Rotation
QVector3D Transform::GetEuler() const
{
    return rotation.toEulerAngles();
}

const QQuaternion& Transform::GetRotation() const
{
    return rotation;
}

QMatrix3x3 Transform::GetRotationMatrix() const
{
    return rotation.toRotationMatrix();
}

//Scale
float Transform::GetScaleX() const
{
    return scale.x();
}

float Transform::GetScaleY() const
{
    return scale.y();
}

float Transform::GetScaleZ() const
{
    return scale.z();
}

const QVector3D& Transform::GetScale() const
{
    return scale;
}

//Setters
//Translation
void Transform::SetTranslationX(float newX)
{
    //Update Vector
    translation.setX(newX);

    //Update Matrix
    transform.setColumn(3, QVector4D(translation, 1.0f));
}

void Transform::SetTranslationY(float newY)
{
    //Update Vector
    translation.setX(newY);

    //Update Matrix
    transform.setColumn(3, QVector4D(translation, 1.0f));
}

void Transform::SetTranslationZ(float newZ)
{
    //Update Vector
    translation.setX(newZ);

    //Update Matrix
    transform.setColumn(3, QVector4D(translation, 1.0f));
}

void Transform::SetTranslation(const QVector3D& newTranslation)
{
    //Update Vector
    translation = newTranslation;

    //Update Matrix
    transform.setColumn(3, QVector4D(translation, 1.0f));
}

//Rotation
void Transform::SetRotation(const QVector3D& euler)
{
    //Update Quaternion
    rotation = QQuaternion::fromEulerAngles(euler);

    //Update Matrix
    UpdateMatrix();
}

void Transform::SetRotation(const QQuaternion& quaternion)
{
    //Update Quaternion
    rotation = quaternion;

    UpdateMatrix();
}

void Transform::SetRotation(const QMatrix3x3& rotationMatrix)
{
    //Update Quaternion
    rotation.fromRotationMatrix(rotationMatrix);

    //Update Matrix
    //Create new matrix
    QMatrix3x3 newMat;
    newMat.setToIdentity();

    //Apply Scale
    newMat(0,0) = scale.x();
    newMat(1,1) = scale.y();
    newMat(2,2) = scale.z();

    //Apply Rotation
    newMat = rotationMatrix * newMat;

    //Add Translation
    transform = QMatrix4x4(newMat);
    transform.setColumn(4, QVector4D(translation, 1.0f));
}

//Scale
void Transform::SetScaleX(float newX)
{
    //Update Vector
    scale.setX(newX);

    //Update Matrix
    UpdateMatrix();
}

void Transform::SetScaleY(float newY)
{
    //Update Vector
    scale.setX(newY);

    //Update Matrix
    UpdateMatrix();
}

void Transform::SetScaleZ(float newZ)
{
    //Update Vector
    scale.setX(newZ);

    //Update Matrix
    UpdateMatrix();
}

void Transform::SetScale(const QVector3D& newScale)
{
    //Update Vector
    scale = newScale;

    //Update Matrix
    UpdateMatrix();
}

//Operators
Transform& Transform::operator = (const Transform& equalTo)
{
    //Matrix
    transform = equalTo.transform;

    //Translation
    translation = equalTo.translation;

    //Rotation
    rotation = equalTo.rotation;

    //Scale
    scale = equalTo.scale;

    return *this;
}

Transform& Transform::operator = (const QMatrix4x4& equalTo)
{
    //Matrix
    transform = equalTo;

    //Translation
    translation = equalTo.column(3).toVector3D();

    //Rotation
    rotation.fromRotationMatrix(transform.toGenericMatrix<3,3>());

    //Scale
    scale.setX(sqrt(equalTo.column(0).lengthSquared()));

    return *this;
}

//QWidget
QWidget* Transform::GenerateWidget()
{
    return new TransformWidget(*this);
}

//Private
void Transform::UpdateMatrix()
{
    //Create new mat
    QMatrix3x3 newMat;
    newMat.setToIdentity();

    //Apply Scale
    newMat(0,0) = scale.x();
    newMat(1,1) = scale.y();
    newMat(2,2) = scale.z();

    //Apply Rotation
    newMat = rotation.toRotationMatrix() * newMat;

    //Add Translation
    transform = QMatrix4x4(newMat);
    transform.setColumn(3, QVector4D(translation, 1.0f));
}
