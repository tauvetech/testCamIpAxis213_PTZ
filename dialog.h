#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QDebug>

#include <QErrorMessage>
#include <QMutex>
//#include <QFileDialog> //pour test de lecture de fichier video
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


// libvlc include
#include <vlc/vlc.h>
#include <vlc/libvlc.h>

namespace Ui {
    class Dialog;
}

#define VIDEO_WIDTH     320 //1024//500
#define VIDEO_HEIGHT    240 //768//450

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;

    void    initVLC();
    bool    catchException();

    QErrorMessage*          errorHandler;

    QString                 mrl;

    // VLC stuff
    static void             lock( struct ctx*, void** );
    static void             unlock( struct ctx* );
    libvlc_exception_t      m_ex;
    libvlc_instance_t*      m_vlcInstance;
    libvlc_media_t*         m_vlcMedia;
    libvlc_media_player_t*  m_vlcMediaplayer;

    //pour requette Http:
    QNetworkAccessManager *manager;
    int valZoom;

signals:
    void                    frameReady( struct ctx* );

private slots:
    void on_pbZoomOut_clicked();
    void on_pbZoomIn_clicked();
    void on_verticalSlider_valueChanged(int value);
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_valueChanged(int value);
    void on_verticalSlider_sliderReleased();
    void on_pbInfos_clicked();
    void on_pbRight_clicked();
    void on_pbLeft_clicked();
    void on_pbDown_clicked();
    void on_pbUp_clicked();
    void on_pbCapture_clicked();
    void on_pbPlay_clicked();
    void on_pbStop_clicked();
    void    processNewFrame( struct ctx* );

    void slot_netwManagerFinished(QNetworkReply*);
};


struct ctx
{
    uchar*      pixels;
    QMutex*     mutex;
    Dialog*     dialog;
};

#endif // DIALOG_H
