#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SettingsWindow){

    ui->setupUi(this);
    this->file = new FileType;

    this->refresh();

    this->setFixedSize(this->size());
}

SettingsWindow::~SettingsWindow(){

    delete file;
    delete ui;

}

void SettingsWindow::refresh(){

    ui->inActive->setChecked(settings.value("inActive") == "True");
    ui->deleteRejected->setChecked(settings.value("deleteRejected") == "True");

    this->change_mode();

}

void SettingsWindow::on_accept_btn_clicked(){

    // Set dialog properties
    QFileDialog dialog;
    dialog.setDirectory(settings.value("acceptDir"));
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);

    // Execute dialog and set dir
    if(!dialog.exec() || !dialog.selectedFiles().length()) return;
    QDir dir = dialog.selectedFiles().first();

    ui->accept->setText(dir.absolutePath());
    settings.setValue("acceptDir", ui->accept->text());

}

void SettingsWindow::on_reject_btn_clicked(){

    // Set dialog properties
    QFileDialog dialog;
    dialog.setDirectory(settings.value("rejectDir"));
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);

    // Execute dialog and set dir
    if(!dialog.exec() || !dialog.selectedFiles().length()) return;
    QDir dir = dialog.selectedFiles().first();

    ui->reject->setText(dir.absolutePath());
    settings.setValue("rejectDir", ui->reject->text());

}

void SettingsWindow::on_pdf_btn_clicked(){

    // Create Dialog
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::homePath());
    dialog.setNameFilters({"PDF files (*.pdf)"});

    // Check Validity
    if(!dialog.exec() || !dialog.selectedFiles().length()) return;

    // Print
    QDir dir = dialog.selectedFiles().first();
    ui->pdf->setText(dir.absolutePath());

    ui->create->setDisabled((ui->pdf->text() == "") || (ui->avi->text() == ""));

}

void SettingsWindow::on_avi_btn_clicked(){

    // Create Dialog
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::homePath());
    dialog.setNameFilters({"AVI files (*.avi)"});

    // Check Validity
    if(!dialog.exec() || !dialog.selectedFiles().length()) return;

    // Print
    QDir dir = dialog.selectedFiles().first();
    ui->avi->setText(dir.absolutePath());

    ui->create->setDisabled((ui->pdf->text() == "") || (ui->avi->text() == ""));

}


void SettingsWindow::on_inActive_stateChanged(int arg1){

    settings.setValue("inActive", arg1 != 0 ? "True" : "False");
    this->change_mode();

}


void SettingsWindow::on_deleteRejected_stateChanged(int arg1){

    settings.setValue("deleteRejected", arg1 != 0 ? "True" : "False");
    this->change_mode();

}

void SettingsWindow::change_mode(){

    if(ui->inActive->isChecked()){
        ui->accept->setText(settings.value("path").append("/accepted"));
        ui->reject->setText(settings.value("path").append("/rejected"));
        ui->accept_btn->setDisabled(true);
        ui->reject_btn->setDisabled(true);

    }else{
        ui->accept->setText(QDir(settings.value("acceptDir")).absolutePath());
        ui->reject->setText(QDir(settings.value("rejectDir")).absolutePath());
        ui->accept_btn->setDisabled(false);
        ui->reject_btn->setDisabled(false);
    }

    if(ui->deleteRejected->isChecked()){
        ui->reject_btn->setDisabled(true);
        ui->reject->setText("");
    }
}

void SettingsWindow::on_create_clicked(){

    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDirectory(QDir::homePath());
    dialog.setNameFilters({"ICVX files (*.icvx)"});

    if(!dialog.exec()) return;
    QDir dir = dialog.directory();

    this->file->create(ui->pdf->text(), ui->avi->text(), dialog.selectedFiles().first());

    if(dir.absolutePath() == settings.value("path"))
        emit file_added();

    // Clear inputs
    ui->pdf->clear();
    ui->avi->clear();

    ui->create->setDisabled(true);

}





