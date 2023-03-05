#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){

    ui->setupUi(this);
    this->setFixedSize(this->size());

    activeItem.is_set = false;

    // Create new objects
    this->w = new SettingsWindow(this);
    this->video = new VideoPlayer(this, ui->videowidget);
    this->file = new FileType;

    // Connect this as QObject to the video player QObject
    this->connectVideo();

    // Setup settings file
    this->setupSettings();

    // Connect to settings screen
    connect(this, &MainWindow::path_changed, w, &SettingsWindow::refresh);
    connect(w, &SettingsWindow::file_added, this, &MainWindow::refresh);

    // Setup file list
    ui->directory->setText(settings.value("path"));
    this->refresh();

    this->volume.last_volume = ui->volume->value();
    this->volume.muted = false;

}


MainWindow::~MainWindow(){

    // Free space on window close (child object will also run destructor)
    delete file;
    delete video;
    delete w;
    delete ui;

}


void MainWindow::setupSettings(){

    // Create entries when empty
    if(!settings.keyExist("path")){
        settings.setValue("path", QDir(".").absolutePath());
        settings.setValue("acceptInActive", QDir("./accepted").absolutePath());
        settings.setValue("rejectInActive", QDir("./rejected").absolutePath());
    }

    if(!settings.keyExist("acceptDir")) settings.setValue("acceptDir", QDir("./accepted").absolutePath());
    if(!settings.keyExist("rejectDir")) settings.setValue("rejectDir", QDir("./rejected").absolutePath());
    if(!settings.keyExist("inActive")) settings.setValue("inActive", "True");
    if(!settings.keyExist("deleteRejected")) settings.setValue("deleteRejected", "False");

}


void MainWindow::connectVideo(){

    // Give progress slider pointer to video object
    video->setProgress(ui->vidProgress);

    //connect singnals to slots
    connect(video, &VideoPlayer::statusChanged, this, &MainWindow::video_status_changed);
    connect(ui->playpause, &QPushButton::clicked, video, &VideoPlayer::playpause);
    connect(ui->stop, &QPushButton::clicked, video, &VideoPlayer::stop);
    connect(ui->volume, &QAbstractSlider::valueChanged, video, &VideoPlayer::setVolume);
    connect(ui->vidProgress, &QAbstractSlider::sliderMoved, video, &VideoPlayer::changeProgress);

    // Sync slider with volume
    video->setVolume(ui->volume->value());

}


void MainWindow::refresh(){

    // Simply refresh the file list
    ui->files->clear();
    ui->files->addItems(QDir(settings.value("path")).entryList(QStringList() << "*.icvx", QDir::Files));

}


void MainWindow::on_browse_clicked(){

    // Set dialog properties
    QFileDialog dialog;
    dialog.setDirectory(settings.value("path"));
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);

    // Execute dialog and set dir
    if(!dialog.exec() || !dialog.selectedFiles().length()) return;
    QDir dir = dialog.selectedFiles().first();

    // Set file chooser
    ui->directory->setText(dir.absolutePath());

    // Set path settings
    settings.setValue("path", ui->directory->text());
    settings.setValue("acceptInActive", QDir(settings.value("path").append("/accepted")).absolutePath());
    settings.setValue("rejectInActive", QDir(settings.value("path").append("/rejected")).absolutePath());

    this->refresh();

    emit this->path_changed();

}


void MainWindow::on_files_itemDoubleClicked(QListWidgetItem *item){

    // Set active item variables
    activeItem.path = QDir(ui->directory->text()).absolutePath();
    activeItem.filename = item->text();
    activeItem.is_set = true;

    video->unload();

    // Load file into temp directory
    QString icvx_path = QString(activeItem.path).append("/").append(activeItem.filename);
    QString pdf_path = QDir::tempPath().append("/icvx_text.tmp");
    QString avi_path = QDir::tempPath().append("/icvx_video.tmp");
    bool loaded = file->load(icvx_path, pdf_path, avi_path);

    // Set video source
    if(loaded) video->setSrc(avi_path);

    // Call ActiveX command to open PDF file
    if(QString(CONTROL) == "Adobe" && loaded){

        ui->pdfview->setControl("Adobe PDF Reader");
        ui->pdfview->dynamicCall("LoadFile(QString)", pdf_path);

    }else if(QString(CONTROL) == "Web" && loaded){

        ui->pdfview->setControl("Microsoft Web Browser");
        ui->pdfview->dynamicCall("Navigate(const QString &)", pdf_path);
        ui->pdfview->dynamicCall("Refresh()", 3);

    }

    // Play the video
    video->play();

    // Set label
    ui->open->setText(activeItem.filename);

}


void MainWindow::on_settings_clicked(){

    // Show settings window
    w->show();

}


void MainWindow::on_accept_btn_clicked(){

    // Return when item is not open
    if(!activeItem.is_set) return;

    // Get user settings
    QString key = settings.value("inActive") == "True" ? "acceptInActive" : "acceptDir";

    // Move the file
    this->movefile(key);

    // Refresh
    this->refresh();

    // Open next
    this->open_next();

}


void MainWindow::on_reject_btn_clicked(){

    // Return when item is not open
    if(!activeItem.is_set) return;

    // If settings say to remove rejected files -> remove and return
    if(settings.value("deleteRejected") == "True" && activeItem.is_set){

        QFile::remove(activeItem.path.append("/").append(activeItem.filename));

        this->refresh();

        this->open_next();

        return;
    }

    // Get user settings
    QString key = settings.value("inActive") == "True" ? "rejectInActive" : "rejectDir";

    // Move the file
    this->movefile(key);

    // Refresh
    this->refresh();

    // Open next
    this->open_next();

}


void MainWindow::movefile(QString key){

    // Return when item is not open
    if(!activeItem.is_set) return;

    // Create QDir object to handle rename method
    QDir dir;

    // When dir does not exist create the path
    if(!QDir(settings.value(key)).exists()) dir.mkpath(settings.value(key));

    // Moves file into directory
    QFile::rename(activeItem.path.append("/").append(activeItem.filename),
                  settings.value(key).append("/").append(activeItem.filename));

}


void MainWindow::video_status_changed(Status s){

    // Switch button value
    if(s == Status::playing){
        ui->playpause->setText("Pause");
        ui->playpause->setIcon(QIcon(":/winicons/graphics/pause.png"));

    }else{
        ui->playpause->setText("Play");
        ui->playpause->setIcon(QIcon(":/winicons/graphics/play.png"));
    }

}


void MainWindow::open_next(){

    // Return when list is empty
    if(!ui->files->count()){

        // Set active item variable
        activeItem.is_set = false;

        // Set label
        ui->open->setText("None");

        return;

    }

    // Call method of item double clicked
    this->on_files_itemDoubleClicked(ui->files->itemAt(0, 0));
    ui->files->setCurrentItem(ui->files->itemAt(0, 0));

}

void MainWindow::on_volume_sliderMoved(int position){

    // Switch in range of volume for icons
    switch(position){
    case 0:
        ui->vol_btn->setIcon(QIcon(":/winicons/graphics/mute.png"));
        break;
    case 1 ... 24:
        ui->vol_btn->setIcon(QIcon(":/winicons/graphics/none.png"));
        break;
    case 25 ... 49:
        ui->vol_btn->setIcon(QIcon(":/winicons/graphics/low.png"));
        break;
    case 50 ... 74:
        ui->vol_btn->setIcon(QIcon(":/winicons/graphics/middle.png"));
        break;
    case 75 ... 100:
        ui->vol_btn->setIcon(QIcon(":/winicons/graphics/high.png"));
        break;
    }

    // Unset muted state
    this->volume.muted = false;

}


void MainWindow::on_vol_btn_clicked(){

    // When muted
    if(this->volume.muted){
        // Set slider and reset icon
        ui->volume->setValue(this->volume.last_volume);
        this->on_volume_sliderMoved(this->volume.last_volume);
        return;
    }

    // Else set last volume, set slider, and reset icon
    this->volume.last_volume = ui->volume->value();
    ui->volume->setValue(0);
    this->on_volume_sliderMoved(0);
    this->volume.muted = true;
}

