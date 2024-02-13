
#include "drawsphere.h"
#include <Qt3DRender/QGeometryRenderer>
#include <QtCore/QDebug>

void drawsphere(Qt3DCore::QEntity *rootEntity, QVector3D centre, double radius, const QColor& color)
{
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_sphereEntity;
    
    // Sphere shape data
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(20);
    sphereMesh->setSlices(20);
    sphereMesh->setRadius(radius);

    // Sphere mesh transform
    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

    sphereTransform->setScale(1.3f);
    sphereTransform->setTranslation(centre);

    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(color);

    // Sphere
    m_sphereEntity = new Qt3DCore::QEntity(rootEntity);
    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);
    m_sphereEntity->addComponent(sphereTransform);
}
