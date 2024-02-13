#include "drawsphere.h"

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <QVector3D>
#include "drawline.h"

#include "3dlinesintersection.h"

#include <iostream>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include <kdl/frames.hpp>


//TODO: unit tests

void deleteChildrenRecursively(const Qt3DCore::QNodeVector& vector)
{
    foreach(Qt3DCore::QNode* node, vector){
        if (node == nullptr) {
            continue;
        }
        
        Qt3DCore::QEntity* entity = dynamic_cast<Qt3DCore::QEntity*>(node);
        if (entity == nullptr) {
            continue;
        }
        
        QList<Qt3DCore::QComponent*> componentsToDelete;
        foreach(Qt3DCore::QComponent* component, entity->components()){
            entity->removeComponent(component);
            delete(component);
            component = nullptr;
        }
        
        deleteChildrenRecursively(node->childNodes());
        delete(node);
        node = nullptr;
    }
}

int main(int argc, char **argv){

    const QColor color_red(QRgb(0xff0000));
    const QColor color_black(QRgb(0x4d4d4f));

    //Qapp
    QApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xffffff)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    QLineEdit *a0_X = new QLineEdit();
    QLineEdit *a0_Y = new QLineEdit();
    QLineEdit *a0_Z = new QLineEdit();
    
    QLineEdit *a1_X = new QLineEdit();
    QLineEdit *a1_Y = new QLineEdit();
    QLineEdit *a1_Z = new QLineEdit();

    QLineEdit *b0_X = new QLineEdit();
    QLineEdit *b0_Y = new QLineEdit();
    QLineEdit *b0_Z = new QLineEdit();

    QLineEdit *b1_X = new QLineEdit();
    QLineEdit *b1_Y = new QLineEdit();
    QLineEdit *b1_Z = new QLineEdit();

    vLayout->addWidget(new QLabel("A0 X:"));
    vLayout->addWidget(a0_X);
    vLayout->addWidget(new QLabel("A0 Y:"));
    vLayout->addWidget(a0_Y);
    vLayout->addWidget(new QLabel("A0 Z:"));
    vLayout->addWidget(a0_Z);

    vLayout->addWidget(new QLabel("A1 X:"));
    vLayout->addWidget(a1_X);
    vLayout->addWidget(new QLabel("A1 Y:"));
    vLayout->addWidget(a1_Y);
    vLayout->addWidget(new QLabel("A1 Z:"));
    vLayout->addWidget(a1_Z);

    vLayout->addWidget(new QLabel("B0 X:"));
    vLayout->addWidget(b0_X);
    vLayout->addWidget(new QLabel("B0 Y:"));
    vLayout->addWidget(b0_Y);
    vLayout->addWidget(new QLabel("B0 Z:"));
    vLayout->addWidget(b0_Z);

    vLayout->addWidget(new QLabel("B1 X:"));
    vLayout->addWidget(b1_X);
    vLayout->addWidget(new QLabel("B1 Y:"));
    vLayout->addWidget(b1_Y);
    vLayout->addWidget(new QLabel("B1 Z:"));
    vLayout->addWidget(b1_Z);
    
    widget->setWindowTitle(QStringLiteral("Intersection of two line segments"));

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Set root object of the scene
    // note: call after modifying rootEntity
    view->setRootEntity(rootEntity);

    // Create control widgets
    QCommandLinkButton *info = new QCommandLinkButton();
    // info->setText(QStringLiteral("Qt3D ready-made meshes"));
    info->setDescription(QString::fromLatin1("Draw line"));
    info->setIconSize(QSize(0,0));

    // vLayout->addWidget(info);

    widget->show();
    widget->resize(1200, 800);

    QPushButton *button = new QPushButton("Calculate Intersection");
    vLayout->addWidget(button);

    KDL::Vector resA;
    KDL::Vector resB;

    QObject::connect(button, &QPushButton::clicked, [&]() {

        view->setRootEntity(rootEntity);
        deleteChildrenRecursively(rootEntity->childNodes());

        // Parse and validate the input from line edits here.
        // Get the coordinates from the line edits
        double a0_X_val = a0_X->text().toDouble();
        double a0_Y_val = a0_Y->text().toDouble();
        double a0_Z_val = a0_Z->text().toDouble();

        double a1_X_val = a1_X->text().toDouble();
        double a1_Y_val = a1_Y->text().toDouble();
        double a1_Z_val = a1_Z->text().toDouble();

        double b0_X_val = b0_X->text().toDouble();
        double b0_Y_val = b0_Y->text().toDouble();
        double b0_Z_val = b0_Z->text().toDouble();

        double b1_X_val = b1_X->text().toDouble();
        double b1_Y_val = b1_Y->text().toDouble();
        double b1_Z_val = b1_Z->text().toDouble();

        // Validate the input (e.g., check for NaN or other invalid values)
        if (std::isnan(a0_X_val) || std::isnan(a0_Y_val) || std::isnan(a0_Z_val) ||
            std::isnan(a1_X_val) || std::isnan(a1_Y_val) || std::isnan(a1_Z_val) ||
            std::isnan(b0_X_val) || std::isnan(b0_Y_val) || std::isnan(b0_Z_val) ||
            std::isnan(b1_X_val) || std::isnan(b1_Y_val) || std::isnan(b1_Z_val)) {
            // Handle invalid input here (display an error message or take appropriate action)
            std::cout << "Invalid input. Please enter valid numbers for all coordinates!" << std::endl;
            return;
        }

        // Convert the input to KDL Vector objects
        KDL::Vector a0(a0_X_val, a0_Y_val, a0_Z_val);
        KDL::Vector a1(a1_X_val, a1_Y_val, a1_Z_val);
        KDL::Vector b0(b0_X_val, b0_Y_val, b0_Z_val);
        KDL::Vector b1(b1_X_val, b1_Y_val, b1_Z_val);

        // Perform the intersection calculation
        int status = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, resA, resB);

        // Update the console with the intersection status and points
        std::cout << "status = " << status << std::endl;
        lines_intersection::PrintVector(resA);
        lines_intersection::PrintVector(resB);

        //Draw lines in 3D
        const QVector3D A_start(a0.x(), a0.y(), a0.z());
        const QVector3D A_end(a1.x(), a1.y(), a1.z());
        drawLine(A_start,A_end, color_black, rootEntity);
        const QVector3D B_start(b0.x(), b0.y(), b0.z());
        const QVector3D B_end(b1.x(), b1.y(), b1.z());
        drawLine(B_start,B_end, color_black, rootEntity);

        // Draw sphere
        double radius = 0.05;
        drawsphere(rootEntity,A_start,radius,color_black);
        drawsphere(rootEntity,A_end,radius,color_black);
        drawsphere(rootEntity,B_start,radius,color_black);
        drawsphere(rootEntity,B_end,radius,color_black);

        if(status==5){
            const QVector3D res_A(resA.x(), resA.y(), resA.z());
            drawsphere(rootEntity,res_A,radius,color_red);
        } else{
            const QVector3D res_A(resA.x(), resA.y(), resA.z());
            drawsphere(rootEntity,res_A,radius,color_black);
            const QVector3D res_B(resB.x(), resB.y(), resB.z());
            drawsphere(rootEntity,res_B,radius,color_black);
            drawLine(res_A,res_B, color_red, rootEntity); 
        }

    });

    return app.exec();

}
