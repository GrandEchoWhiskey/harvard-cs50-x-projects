#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QMap>
#include <QListWidget>
#include <QIcon>

#include "settingswindow.h"
#include "videoplayer.h"
#include "filetype.h"
#include "settings.h"

//! Use: "Adobe", or "Web" only. otherwise program will not show PDF.
//! When Adobe Reader ActiveX is installed just use "Adobe" - preferred.
#define CONTROL "Adobe"


/*
    MainWindow is a class that contains the whole graphical user interface.
*/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


signals:

    void path_changed();

public slots:

    void video_status_changed(Status s);

    void refresh();

private slots:

    void on_browse_clicked();

    void on_files_itemDoubleClicked(QListWidgetItem *item);

    void on_settings_clicked();

    void on_accept_btn_clicked();

    void on_reject_btn_clicked();

    void open_next();


    void on_volume_sliderMoved(int position);

    void on_vol_btn_clicked();

private:

    void connectVideo();

    void setupSettings();

    void movefile(QString key);


    Ui::MainWindow *ui;

    VideoPlayer *video;

    FileType *file;

    SettingsWindow *w;


    Settings settings;


    struct {
        bool is_set;
        QString path;
        QString filename;
    } activeItem;


    struct {
        bool muted;
        int last_volume;
    } volume;


};

#endif // MAINWINDOW_H
