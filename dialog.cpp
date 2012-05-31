#include "dialog.h"
#include "ui_dialog.h"

#include <stdio.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // Forget that for the moment ;-)
    connect( this, SIGNAL( frameReady( struct ctx* ) ),
             this, SLOT( processNewFrame( struct ctx* ) ) );

    initVLC();

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished(QNetworkReply*)));

    valZoom = 1;
    this->on_pbInfos_clicked();
}

Dialog::~Dialog()
{
    delete ui;
    //arret du flux video si oubli de faire stop:
    if(libvlc_media_player_is_playing(m_vlcMediaplayer, &m_ex))
    {
        libvlc_media_player_stop(m_vlcMediaplayer, &m_ex);
//        libvlc_instance_t*      m_vlcInstance;
//        libvlc_media_t*         m_vlcMedia;
//        libvlc_media_player_t*  m_vlcMediaplayer;
    }

    manager->~QNetworkAccessManager();
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//Initialisation de VLC:
void Dialog::initVLC()
{
    // List of parameters used to initialize libvlc.
    // These arguments are same as those you can pass
    // the the VLC command line.
    char const* vlc_argv[] =
    {
        "--verbose", "3",
        // Edit this line if libvlc can't locate your plugins directory
        "--plugin-path=D:\\Libs\\vlc-1.0.5\\plugins\\",
        "--rtsp-caching=30" //pour avoir un flux "temps reel"...
    };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

    // Initialize the libvlc exception mechanism
    libvlc_exception_init( &m_ex );
    // Create a libvlc instance
    m_vlcInstance = libvlc_new( vlc_argc, vlc_argv, &m_ex );
    // This for catching and printing exceptions
    // raised by libvlc
    this->catchException();
    // Create the mediaplayer used to play a media
    m_vlcMediaplayer = libvlc_media_player_new( m_vlcInstance, &m_ex );
    // Re-checking for exceptions
    catchException();

    // We're done with the initialization!
}

bool Dialog::catchException()
{
    if ( libvlc_exception_raised( &m_ex ) )
    {
        /* For VLC <= 1.0.x */
        errorHandler->showMessage( libvlc_exception_get_message( &m_ex ) );
        /* For VLC >= 1.1.x */
        //errorHandler->showMessage( libvlc_errmsg() );
        libvlc_exception_clear( &m_ex );
        return true;
    }
    return false;
}

void Dialog::on_pbPlay_clicked()
{
    // This method is called, when the play button is
    // clicked.

    if ( mrl.isEmpty() )
    {
// //Show the open dialog
//        mrl = QFileDialog::getOpenFileName( this,
//                                            "Open a video file",
//                                            QDir::home().dirName(),
//                                            "Videos (*.avi *.ogg *.mkv "
//                                            "*.mpg *.mpeg *.wmv)" );


        mrl = "rtsp://192.168.0.90/mpeg4/media.amp";
        //test (for ElphelCam) (work! only once time ...)
        //mrl = "rtsp://192.168.0.9/mpeg4/media.amp";

        if ( mrl.isEmpty() ) return;

        // Create a new media from the Media Resource Locator
        m_vlcMedia = libvlc_media_new( m_vlcInstance, mrl.toAscii(), &m_ex );
        // Catching exception
        catchException();

        // We now need a struct for storing the video buffer
        // and a mutex to protect it.
        // The structure will be given as an arguments for the
        // lock/unlock callbacks.
        struct ctx* context;
        // Allocating the space for the structure
        context = ( struct ctx* )malloc( sizeof( *context ) );
        // Allocating the video buffer
        context->pixels = ( uchar* )malloc( ( sizeof( *( context->pixels ) ) * VIDEO_WIDTH * VIDEO_HEIGHT ) * 4 );
        // Allocating the mutex
        context->mutex = new QMutex();
        context->dialog = this;

        // Creating some char[] to store the media options
        char clock[64], cunlock[64], cdata[64];
        char width[32], height[32], chroma[32], pitch[32];

        // Preparing the options for the media
        // The clock and cunlock contain a pointer to the associated
        // static method (note the use of %lld).
        //
        // In that specific case we can't use Qt:
        // The sprintf method of the QString does not support
        // length modifiers (like %lld).
        sprintf( clock,   ":vmem-lock=%lld",   (long long int)(intptr_t)lock    );
        sprintf( cunlock, ":vmem-unlock=%lld", (long long int)(intptr_t)unlock  );
        sprintf( cdata,   ":vmem-data=%lld",   (long long int)(intptr_t)context );
        sprintf( width,   ":vmem-width=%i",    VIDEO_WIDTH                      );
        sprintf( height,  ":vmem-height=%i",   VIDEO_HEIGHT                     );
        sprintf( chroma,  ":vmem-chroma=%s",   "RV32"                           );
        sprintf( pitch,   ":vmem-pitch=%i",    VIDEO_WIDTH * 4                  );

        // List of options
        // This part can be easily replaced by a QStringList
        // instead of a C array.
        char const* media_options[] =
        {
            ":vout=vmem",
            width, height,
            chroma, pitch,
            clock, cunlock,
            cdata
        };
        int media_options_size = sizeof( media_options )
                                 / sizeof( *media_options );

        // Adding each option from the array to the media
        for ( int i = 0; i < media_options_size; ++i )
        {
            libvlc_media_add_option( m_vlcMedia, media_options[i], &m_ex );
            catchException();
        }

        // Put the media into the mediaplayer
        libvlc_media_player_set_media( m_vlcMediaplayer, m_vlcMedia, &m_ex );
        catchException();
    }

    // Finally, start the playback.
    libvlc_media_player_play( m_vlcMediaplayer, &m_ex );
    catchException();

}

void Dialog::lock( struct ctx* ctx, void** pp_ret )
{
    // Lock the buffer (to avoid concurrent access and data corruption)
  //ctx->mutex->lock();
    // Tell libvlc to write the next frame into our pre-allocated buffer
    *pp_ret = ctx->pixels;
}

void Dialog::unlock( struct ctx* ctx )
{
    // As we are in a static method we don't have an instance
    // of the MainWindow here. Fortunately we created a copy
    // of our instance pointer into the ctx structure,
    // do you remember ?
    ctx->dialog->emit frameReady( ctx );
    // That way we are able to emit a signal containing our
    // new video frame !
}

void Dialog::processNewFrame( struct ctx* ctx )
{
    // WARNING:
    // This part of the code is extremely slow and inefficient
    // (but sufficient for our example).

    // The bottleneck starts here ;)

    // Conversion of the frame from our pixel buffer to a QImage
    QImage px( ctx->pixels, VIDEO_WIDTH, VIDEO_HEIGHT, QImage::Format_RGB32 );
    // Then we're creating a new QPixmap from our QImage
    QPixmap pix = QPixmap::fromImage( px );

    // Set the current frame into the video container
    //video->setPixmap( pix );
    ui->labelVideo->setPixmap( pix );

    // Releasing the mutex for the upcoming frame.
  //ctx->mutex->unlock();
}



void Dialog::on_pbStop_clicked()
{
    libvlc_media_player_stop(m_vlcMediaplayer, &m_ex);
}

void Dialog::on_pbCapture_clicked()
{
    //test image on the web:
    //    QUrl url("http://farm5.static.flickr.com/4101/4798839454_725882374d_b.jpg");
    //    QNetworkRequest request(url);

    QNetworkRequest request;
    //test(for Elphel Cam)(work!)
    //request.setUrl(QUrl("http://192.168.0.9:8081/bimg"));
    request.setUrl(QUrl("http://192.168.0.90/jpg/image.jpg"));
    manager->get(request);

}

void Dialog::slot_netwManagerFinished(QNetworkReply *reply)
{
    qDebug() << "ContentType:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();

    QString _contentTypeHeader = QString(reply->header(QNetworkRequest::ContentTypeHeader).toString());
    if(_contentTypeHeader.isEmpty())
    {
        qDebug() << "ContentType: vide, rien a recuperer ...";
        if (reply->error() != QNetworkReply::NoError)
                qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }
    if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
            return;
        }
        QVariant attribute = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if (attribute.isValid()) {
            QUrl url = attribute.toUrl();
            qDebug() << "must go to:" << url;
            return;
        }
        QString contentTypeHeader = QString(reply->header(QNetworkRequest::ContentTypeHeader).toString());

        qDebug() << "ContentType:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        if(contentTypeHeader.isEmpty())
        {
            qDebug() << "ContentType: vide, rien a recuperer ...";
        }
        else
            if (contentTypeHeader == "text/plain")
            {
            //ui->plainTextEdit->setPlainText(reply->readAll());

            QString strPan = QString(reply->readLine()); //pan=valeur.valeur
            strPan.remove(0,4);                          //valeur.valeur //on ôte "pan="
            ui->labelValeurPan->setText(strPan);         //on affiche la valeur.
            QString strTilt = QString(reply->readLine()); //tilt=valeur.valeur
            strTilt.remove(0,5);                           //on ôte "tilt="
            ui->labelValeurTilt->setText(strTilt);
            QString strZoom = QString(reply->readLine()); //zoom=valeur.valeur
            strZoom.remove(0,5);                          //on ôte "zoom="
            ui->labelValeurZoom->setText(strZoom);

            ui->labelPanValue->setText(strPan);
            ui->labelTiltValue->setText(strTilt);

            ui->plainTextEdit->setPlainText(strPan);
            ui->plainTextEdit->appendPlainText(strTilt);
            ui->plainTextEdit->appendPlainText(strZoom);
            ui->plainTextEdit->appendPlainText(reply->readAll());
            }
            else
            {
                if (contentTypeHeader == "image/jpeg")
                {
                    QByteArray jpegData = reply->readAll();
                    QPixmap pixmap;
                    pixmap.loadFromData(jpegData);
                    ui->labelCapture->setPixmap(pixmap);
                    pixmap.save("image.bmp");
                }


            }
        //reply->deleteLater(); ???
}


void Dialog::on_pbUp_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?move=up"));
    manager->get(request);
}

void Dialog::on_pbDown_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?move=down"));
    manager->get(request);
}

void Dialog::on_pbLeft_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?move=left"));
    manager->get(request);
}

void Dialog::on_pbRight_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?move=right"));
    manager->get(request);
}

void Dialog::on_pbInfos_clicked()
{
    QNetworkRequest request;
    //request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?info=1&camera=1"));
    request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?query=position&camera=1"));
    //request.setUrl(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?query=presetposcam"));

    manager->get(request);
}

void Dialog::on_verticalSlider_sliderReleased()
{
    int value = ui->verticalSlider->value();
    qDebug() << "valeur Vertical (TILT) slider : "<< value << endl;
    QString val = QString().setNum(value);
    qDebug() << "valeur val : "<< val << endl;
    QString adr = QString("http://192.168.0.90/axis-cgi/com/ptz.cgi?tilt=").append(val);
    qDebug()<< "valAdr : "<<adr<<endl;
    QNetworkRequest request;
    request.setUrl(QUrl(adr));
    manager->get(request);
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "on_horizontalSlider_valueChanged :"<< value << endl;
    QString val = QString().setNum(value);
    ui->labelPanValue->setText(val);
}

void Dialog::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    qDebug() << "valeur horizontal (PAN) slider : "<< value << endl;
    QString val = QString().setNum(value);
    qDebug() << "valeur val : "<< val << endl;
    QString adr = QString("http://192.168.0.90/axis-cgi/com/ptz.cgi?pan=").append(val);
    qDebug()<< "valAdr : "<<adr<<endl;
    QNetworkRequest request;
    request.setUrl(QUrl(adr));
    manager->get(request);
}

void Dialog::on_verticalSlider_valueChanged(int value)
{
    qDebug() << "on_verticalSlider_valueChanged :"<< value << endl;
    QString val = QString().setNum(value);
    ui->labelTiltValue->setText(val);
}

void Dialog::on_pbZoomIn_clicked()
{

    //Syntax:
    //http://<servername>/axis-cgi/com/ptz.cgi?<parameter>=<value>[&<parameter>=<value>...]

    if (valZoom < 10000)
        valZoom += 1000;

    if (valZoom > 9999)
        valZoom = 9999;


    QString val = QString().setNum(valZoom);
    QString adr = QString("http://192.168.0.90/axis-cgi/com/ptz.cgi?zoom=").append(val);
    qDebug()<< "valZoomIn : "<<adr<<endl;
    QNetworkRequest request;
    request.setUrl(QUrl(adr));
    manager->get(request);

}

void Dialog::on_pbZoomOut_clicked()
{
    if (valZoom > 0)
        valZoom -= 1000;

    if (valZoom < 1)
        valZoom = 1;

    QString val = QString().setNum(valZoom);
    QString adr = QString("http://192.168.0.90/axis-cgi/com/ptz.cgi?zoom=").append(val);
    qDebug()<< "valZoomOut : "<<adr<<endl;
    QNetworkRequest request;
    request.setUrl(QUrl(adr));
    manager->get(request);
}
