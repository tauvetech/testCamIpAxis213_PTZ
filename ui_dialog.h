/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Fri 25. May 11:44:35 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pbUp;
    QLabel *labelVideo;
    QSlider *horizontalSlider;
    QPushButton *pbZoomIn;
    QSlider *verticalSlider;
    QLabel *labelPanValue;
    QPushButton *pbPlay;
    QPushButton *pbStop;
    QPushButton *pbCapture;
    QLabel *labelTiltValue;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *labelPan;
    QLabel *labelTilt;
    QLabel *labelZoom;
    QLabel *labelValeurZoom;
    QLabel *labelValeurTilt;
    QLabel *labelValeurPan;
    QPushButton *pbInfos;
    QLabel *labelCapture;
    QPushButton *pbDown;
    QPushButton *pbLeft;
    QPushButton *pbRight;
    QPushButton *pbZoomOut;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(680, 444);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(160);
        sizePolicy.setVerticalStretch(120);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        pbUp = new QPushButton(Dialog);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));
        pbUp->setGeometry(QRect(150, 358, 41, 31));
        labelVideo = new QLabel(Dialog);
        labelVideo->setObjectName(QString::fromUtf8("labelVideo"));
        labelVideo->setGeometry(QRect(9, 9, 320, 240));
        labelVideo->setFrameShape(QFrame::StyledPanel);
        labelVideo->setFrameShadow(QFrame::Plain);
        labelVideo->setLineWidth(1);
        labelVideo->setMidLineWidth(0);
        labelVideo->setScaledContents(true);
        labelVideo->setAlignment(Qt::AlignCenter);
        horizontalSlider = new QSlider(Dialog);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 260, 321, 26));
        horizontalSlider->setMinimum(-170);
        horizontalSlider->setMaximum(170);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);
        horizontalSlider->setTickInterval(5);
        pbZoomIn = new QPushButton(Dialog);
        pbZoomIn->setObjectName(QString::fromUtf8("pbZoomIn"));
        pbZoomIn->setGeometry(QRect(10, 360, 61, 31));
        verticalSlider = new QSlider(Dialog);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(340, 10, 26, 241));
        verticalSlider->setMinimum(-10);
        verticalSlider->setMaximum(90);
        verticalSlider->setSliderPosition(0);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickPosition(QSlider::TicksAbove);
        verticalSlider->setTickInterval(10);
        labelPanValue = new QLabel(Dialog);
        labelPanValue->setObjectName(QString::fromUtf8("labelPanValue"));
        labelPanValue->setGeometry(QRect(10, 280, 43, 16));
        pbPlay = new QPushButton(Dialog);
        pbPlay->setObjectName(QString::fromUtf8("pbPlay"));
        pbPlay->setGeometry(QRect(93, 300, 75, 23));
        pbStop = new QPushButton(Dialog);
        pbStop->setObjectName(QString::fromUtf8("pbStop"));
        pbStop->setGeometry(QRect(180, 300, 75, 23));
        pbCapture = new QPushButton(Dialog);
        pbCapture->setObjectName(QString::fromUtf8("pbCapture"));
        pbCapture->setGeometry(QRect(410, 60, 75, 23));
        labelTiltValue = new QLabel(Dialog);
        labelTiltValue->setObjectName(QString::fromUtf8("labelTiltValue"));
        labelTiltValue->setGeometry(QRect(360, 10, 39, 16));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(520, 170, 101, 84));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelPan = new QLabel(groupBox);
        labelPan->setObjectName(QString::fromUtf8("labelPan"));

        gridLayout->addWidget(labelPan, 0, 0, 1, 1);

        labelTilt = new QLabel(groupBox);
        labelTilt->setObjectName(QString::fromUtf8("labelTilt"));

        gridLayout->addWidget(labelTilt, 1, 0, 1, 1);

        labelZoom = new QLabel(groupBox);
        labelZoom->setObjectName(QString::fromUtf8("labelZoom"));

        gridLayout->addWidget(labelZoom, 2, 0, 1, 1);

        labelValeurZoom = new QLabel(groupBox);
        labelValeurZoom->setObjectName(QString::fromUtf8("labelValeurZoom"));

        gridLayout->addWidget(labelValeurZoom, 2, 1, 1, 1);

        labelValeurTilt = new QLabel(groupBox);
        labelValeurTilt->setObjectName(QString::fromUtf8("labelValeurTilt"));

        gridLayout->addWidget(labelValeurTilt, 1, 1, 1, 1);

        labelValeurPan = new QLabel(groupBox);
        labelValeurPan->setObjectName(QString::fromUtf8("labelValeurPan"));

        gridLayout->addWidget(labelValeurPan, 0, 1, 1, 1);

        pbInfos = new QPushButton(Dialog);
        pbInfos->setObjectName(QString::fromUtf8("pbInfos"));
        pbInfos->setGeometry(QRect(410, 200, 75, 23));
        labelCapture = new QLabel(Dialog);
        labelCapture->setObjectName(QString::fromUtf8("labelCapture"));
        labelCapture->setGeometry(QRect(500, 10, 160, 120));
        labelCapture->setMinimumSize(QSize(160, 120));
        labelCapture->setMaximumSize(QSize(160, 120));
        labelCapture->setFrameShape(QFrame::StyledPanel);
        labelCapture->setScaledContents(true);
        labelCapture->setAlignment(Qt::AlignCenter);
        pbDown = new QPushButton(Dialog);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));
        pbDown->setGeometry(QRect(150, 398, 41, 31));
        pbLeft = new QPushButton(Dialog);
        pbLeft->setObjectName(QString::fromUtf8("pbLeft"));
        pbLeft->setGeometry(QRect(100, 380, 41, 31));
        pbRight = new QPushButton(Dialog);
        pbRight->setObjectName(QString::fromUtf8("pbRight"));
        pbRight->setGeometry(QRect(200, 380, 41, 31));
        pbZoomOut = new QPushButton(Dialog);
        pbZoomOut->setObjectName(QString::fromUtf8("pbZoomOut"));
        pbZoomOut->setGeometry(QRect(10, 390, 61, 31));
        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(420, 290, 244, 139));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "testCamIP_AXIS_213_PTZ", 0, QApplication::UnicodeUTF8));
        pbUp->setText(QApplication::translate("Dialog", "UP", 0, QApplication::UnicodeUTF8));
        labelVideo->setText(QApplication::translate("Dialog", "labelVideo", 0, QApplication::UnicodeUTF8));
        pbZoomIn->setText(QApplication::translate("Dialog", "Zoom IN", 0, QApplication::UnicodeUTF8));
        labelPanValue->setText(QApplication::translate("Dialog", "PanValue", 0, QApplication::UnicodeUTF8));
        pbPlay->setText(QApplication::translate("Dialog", "Play", 0, QApplication::UnicodeUTF8));
        pbStop->setText(QApplication::translate("Dialog", "Stop", 0, QApplication::UnicodeUTF8));
        pbCapture->setText(QApplication::translate("Dialog", "Capture", 0, QApplication::UnicodeUTF8));
        labelTiltValue->setText(QApplication::translate("Dialog", "TiltValue", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "PTZ :", 0, QApplication::UnicodeUTF8));
        labelPan->setText(QApplication::translate("Dialog", "PAN :", 0, QApplication::UnicodeUTF8));
        labelTilt->setText(QApplication::translate("Dialog", "TILT :", 0, QApplication::UnicodeUTF8));
        labelZoom->setText(QApplication::translate("Dialog", "ZOOM :", 0, QApplication::UnicodeUTF8));
        labelValeurZoom->setText(QApplication::translate("Dialog", "?", 0, QApplication::UnicodeUTF8));
        labelValeurTilt->setText(QApplication::translate("Dialog", "?", 0, QApplication::UnicodeUTF8));
        labelValeurPan->setText(QApplication::translate("Dialog", "?", 0, QApplication::UnicodeUTF8));
        pbInfos->setText(QApplication::translate("Dialog", "Infos", 0, QApplication::UnicodeUTF8));
        labelCapture->setText(QApplication::translate("Dialog", "labelCapture", 0, QApplication::UnicodeUTF8));
        pbDown->setText(QApplication::translate("Dialog", "DOWN", 0, QApplication::UnicodeUTF8));
        pbLeft->setText(QApplication::translate("Dialog", "LEFT", 0, QApplication::UnicodeUTF8));
        pbRight->setText(QApplication::translate("Dialog", "RIGHT", 0, QApplication::UnicodeUTF8));
        pbZoomOut->setText(QApplication::translate("Dialog", "Zoom Out", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
